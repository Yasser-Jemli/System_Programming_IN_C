#include "database_file_management.h"


int create_new_database_file(char *filename){
    int file_descriptor = open(filename , O_RDONLY);
    if (file_descriptor != STATUS_ERROR){
        perror("open");
        printf("Error : file already exist ! \n");
        close(file_descriptor);
        return STATUS_ERROR ; 
    }

    file_descriptor = open (filename , O_RDWR | O_CREAT , 0644);
    if(file_descriptor == STATUS_ERROR){
        perror("open");
        printf("Error : Error while trying to create the file !\n");
        close(file_descriptor);
        return STATUS_ERROR ; 
    }

    return file_descriptor ; 
}

int open_database_file(char *filename){
    int file_descriptor = open(filename , O_RDWR);
    if(file_descriptor == STATUS_ERROR){
        perror("open");
        printf("Error : Error while trying to read the database file given by the user\n");
        close (file_descriptor);
        return STATUS_ERROR ; 
    }

    return file_descriptor ;
}

int add_database_header_information(int file_descriptor){
    if (file_descriptor < 0 ){
        printf("Bad File descriptor is given for database file ! \n");
        return STATUS_ERROR ; 
    }
    struct database_header *my_database_header = calloc(1,sizeof(struct database_header));
    if (my_database_header == NULL){
        printf("Error in calloc: Memory allocation failed\n");
        return STATUS_ERROR ;
    }

    my_database_header->magic_number = htonl(MAGIC_NUMBER);
    my_database_header->filesize = htonl(sizeof(struct database_header));
    my_database_header->employee_count = htons(0);
    my_database_header->version = htons(DATABASE_FILE_VERSION);
        
    #ifdef DEBUG
    printf(" Writing Magic Number: 0x%X\n", my_database_header->magic_number);
    #endif

    // Write the structure to the file
    ssize_t written_bytes = write(file_descriptor, my_database_header, sizeof(struct database_header));
    if (written_bytes != sizeof(struct database_header)) {
        perror("write");
        printf("Error: Failed to write header to the database file\n");
        free(my_database_header);
        return STATUS_ERROR;
    }

    free(my_database_header);
    return STATUS_SUCCESS;
}


int verifiy_database_header_information(int file_descriptor) {
    if (file_descriptor == -1) {
        perror("Invalid file descriptor");
        return STATUS_ERROR;
    }

    struct database_header database_file_header;

    ssize_t read_file_header = read(file_descriptor, &database_file_header, sizeof(struct database_header));
    if (read_file_header == -1) {
        perror("Error reading database header");
        close(file_descriptor);
        return STATUS_ERROR;
    }

    // Debug print - only compiled if DEBUG is defined
    #ifdef DEBUG
    printf("Raw Read Magic Number: 0x%X\n", database_file_header.magic_number);
    #endif

    // Convert values from network to host byte order
    database_file_header.version = ntohs(database_file_header.version);
    database_file_header.filesize = ntohl(database_file_header.filesize);
    database_file_header.employee_count = ntohs(database_file_header.employee_count);
    database_file_header.magic_number = ntohl(database_file_header.magic_number);

    // Debug print - only compiled if DEBUG is defined
    #ifdef DEBUG
    printf("Converted Magic Number: 0x%X\n", database_file_header.magic_number);
    printf("Magic Number is : 0x%X\n", MAGIC_NUMBER);
    #endif

    if (database_file_header.magic_number != MAGIC_NUMBER) {
        printf("❌ Corrupted Database file! Magic number mismatch!\n");
        close(file_descriptor);
        return STATUS_ERROR;
    }

    if (database_file_header.version != DATABASE_FILE_VERSION) {
        printf("❌ Corrupted Database file: Version mismatch! Expected: %d, Found: %d\n", DATABASE_FILE_VERSION, database_file_header.version);
        close(file_descriptor);
        return STATUS_ERROR;
    }

    struct stat database_file_state;
    if (fstat(file_descriptor, &database_file_state) == -1) {
        perror("Error with fstat");
        close(file_descriptor);
        return STATUS_ERROR;
    }

    if (database_file_header.filesize != (unsigned int)database_file_state.st_size) {
        printf("❌ File size mismatch! Expected size: %u, Found: %lu\n", database_file_header.filesize, database_file_state.st_size);
        close(file_descriptor);
        return STATUS_ERROR;
    }

    printf("Verification of the database file was successful.\n");
    return STATUS_SUCCESS;
}

int read_database_file_header(int file_descriptor , struct database_header **file_db_header){
    if (file_descriptor == STATUS_ERROR){
        perror("Bad file descriptor is given ! \n");
        close(file_descriptor); 
        return STATUS_ERROR ; 
    }

    struct database_header *db_header = calloc(1 , sizeof(struct database_header));
    if (db_header == NULL){
        perror("Failed to calloc database header structure \n");
        return STATUS_ERROR ; 
    } 

    if (read(file_descriptor , db_header , sizeof(struct database_header)) == STATUS_ERROR){
        perror("Failed to read database header from file"); 
        free(db_header);
        return STATUS_ERROR ;
    }

    printf("Magic Number is : %d " , db_header->magic_number);

    *file_db_header = db_header;
    return STATUS_SUCCESS ; 
}

int write_updates_to_database_file(int file_descriptor , struct database_header *db_header , struct employees *db_employees){
    if (file_descriptor == STATUS_ERROR){
        perror("Bad file descriptor \n");
        return STATUS_ERROR ;
    }

    int employees_final_count = db_header->employee_count ;
    //printf("Employees count while try to writting to the file is : %d \n" , employees_final_count);

    db_header->employee_count = htons(db_header->employee_count);
    db_header->magic_number = htonl(db_header->magic_number);
    db_header->version = htons(db_header->version);
    db_header->filesize = htonl(sizeof(struct database_header) + sizeof(struct employees) * employees_final_count);

    // printf("header Magic number is : %d \n" , ntohl(db_header->magic_number));
    // printf("file size is : %d \n" , ntohl(db_header->filesize));
    // printf("Version is : %d \n" , ntohs(db_header->version));
    // printf("Em ployee count also is : %d\n" , ntohs(db_header->employee_count));

    lseek(file_descriptor , 0 , SEEK_SET); 
    ssize_t writtenbytes =  write(file_descriptor , db_header , sizeof(struct database_header));
    if(writtenbytes != sizeof(struct database_header)){
        perror("Error writing updates to the file , exit ! \n");
        return STATUS_ERROR ;
    }

    int employees_num = 0;
	for (; employees_num < employees_final_count; employees_num++) {
		db_employees[employees_num].id = htonl(db_employees[employees_num].id);
        db_employees[employees_num].required_hours = htonl(db_employees[employees_num].required_hours);
		write(file_descriptor, &db_employees[employees_num], sizeof(struct employees));
        printf("My employee is : %s %s \n" , db_employees[employees_num].firstname , db_employees[employees_num].lastname);
        printf("the id and required hours are : %d  : %d\n" , ntohl(db_employees[employees_num].id) , ntohl(db_employees[employees_num].required_hours) );
	}

    fsync(file_descriptor);
    return STATUS_SUCCESS ;

}

void read_database_file(int file_descriptor) {
    struct database_header db_header;
    lseek(file_descriptor, 0, SEEK_SET);
    read(file_descriptor, &db_header, sizeof(struct database_header));

    db_header.employee_count = ntohs(db_header.employee_count);
    db_header.magic_number = ntohl(db_header.magic_number);
    db_header.version = ntohs(db_header.version);
    db_header.filesize = ntohl(db_header.filesize);

    printf("Header - Magic: %d, Version: %d, Employee Count: %d, Filesize: %d\n",
           db_header.magic_number, db_header.version, db_header.employee_count, db_header.filesize);

    struct employees db_employees[db_header.employee_count];
    for (int i = 0; i < db_header.employee_count; i++) {
        read(file_descriptor, &db_employees[i], sizeof(struct employees));

        db_employees[i].id = ntohl(db_employees[i].id);
        db_employees[i].required_hours = ntohl(db_employees[i].required_hours);

        printf("Employee %d - ID: %d, Required Hours: %d, Firstname: %s, Lastname: %s\n",
               i, db_employees[i].id, db_employees[i].required_hours, db_employees[i].firstname, db_employees[i].lastname);
    }
}
