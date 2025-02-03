#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "common.h"
#include "database_file_management.h"
#include "employees_management.h"

int main(int argc , char *argv[]){

    int opt ;
    int database_file_descriptor = -1 ;
    int database_file_fd = -1 ;
    bool newfile = false ;
    bool listfile = false ;
    char *databasefile = NULL ;
    char *new_employee = NULL ;
    char filename[] = "./local_database_file.db" ;

    while (( opt = getopt(argc , argv , "ne:a:lh")) != -1){
        switch(opt){
            case 'n':
                newfile = true ; // to create new database file 
                break ;
            case 'e':
                databasefile = optarg; // to give the path of an existing database file 
                printf("exist database file entered by the User is %s\n" , optarg);
                break ;
            case 'a':
                new_employee = optarg; // to add new employee data
                break ;
            case 'l':
                printf("Listing all the employees in the database\n");
                listfile = true ;
                break ;  
            case 'h':
                printf("************ Showing the Help Menu ************** \n");
                show_help_menu();
                break ;
            case '?':
                printf("Unkown option or missing argument %c\n" , optopt);
                break ; 
            default :
                printf("***** No argument is given : Error \n");
                printf("Run the Porgram with -h flag to show help menu \n");
                printf("Usage : %s -f \n", argv[0]);
                return -1 ;

        }
    }

    // handle the flag n for createing new database file and the -f for existing file 
    if(newfile){
        database_file_descriptor = create_new_database_file(filename);
        
        if (database_file_descriptor == STATUS_ERROR){
            printf("Failed to create new database file !\n");
            return STATUS_ERROR ;
        }

        ssize_t write_header = add_database_header_information(database_file_descriptor);
        if (write_header == STATUS_ERROR){
            printf("Failed to write header to the database file \n");
        }

        databasefile = filename ; 

    } else {
        if (databasefile == NULL){
            printf("No Given file is entered by the user\n"); 
            return STATUS_ERROR ; 
        } else {
            database_file_descriptor = open_database_file(databasefile);
            if (database_file_descriptor == STATUS_ERROR){
                printf("Failed to open the database file given by the user ! \n");
                return STATUS_ERROR ; 
            }

            int validate_database_file_header = verifiy_database_header_information(database_file_descriptor);
            if (validate_database_file_header != STATUS_SUCCESS){
                printf("Error : Error validating database header ,exit !\n");
                close(database_file_descriptor);
            }


        }
    }

    close(database_file_descriptor);

    // Process now with other argument which will require the database file to be opened 

    // Necessarry Declaration 
    struct database_header *database_file_header = NULL ;
    struct employees *database_file_employees = NULL ;

    database_file_fd = open_database_file(databasefile);
    if (database_file_fd == STATUS_ERROR){
        perror("Failed to open database file : ");
        return STATUS_ERROR ; 
    }

    if (listfile){
        read_database_file(database_file_descriptor);
    }
    
    int database_file_hd = verifiy_database_header_information(database_file_fd);
    if(database_file_hd != STATUS_SUCCESS){
        printf("Error : Error validating database header ,exit !\n");
        close(database_file_hd);
    }
    printf("Verification of Header was done successfuly no issue : we can move forward !\n");
    lseek(database_file_fd, 0, SEEK_SET);  // Move the file pointer to the beginning

    int read_status = read_database_file_header(database_file_fd , &database_file_header);
    if (read_status != STATUS_SUCCESS){
        perror("issue while reading and parsing header of database file !\n");
        return STATUS_ERROR ;
    } else{
        printf("Magic Number: %x\n", database_file_header->magic_number);
        printf("Version: %d\n", database_file_header->version);
        printf("Employee Count: %d\n", database_file_header->employee_count);
        printf("File Size: %d\n", database_file_header->filesize);
    }

    if(new_employee){
        //add_new_employee_to_database_file(database_file_fd , )
        // printf("databse file employees count is : %d \n" , database_file_header->employee_count);
        database_file_header->employee_count++;
        // printf("databse file employees count is : %d \n" , database_file_header->employee_count);
        database_file_employees = realloc(database_file_employees , sizeof(database_file_header->employee_count * sizeof(struct employees)));
        // printf("Database Header count is set now to %d \n" , database_file_header->employee_count);
        // printf("Database header magic number is : %d \n" , database_file_header->magic_number);
        add_new_employee_to_database_file(database_file_header , database_file_employees , new_employee);
        write_updates_to_database_file(database_file_fd , database_file_header , database_file_employees);
    }

    // free(database_file_header);
    // free(database_file_employees);
    close(database_file_fd);
    return STATUS_SUCCESS ; 
}