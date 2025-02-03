#ifndef DATABASE_FILE_MANAGEMENT_H
#define DATABASE_FILE_MANAGEMENT_H 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdint.h>

#include "common.h"
#include "employees.h"


// Define DEBUG for enabling debug output , to be removed later 
#define DEBUG


#define MAGIC_NUMBER 0x54CEC300
#define DATABASE_FILE_VERSION 0x01


#pragma pack(push, 1)  // Save previous alignment and set packing to 1 byte

struct database_header {
    unsigned int magic_number;
    unsigned short version;
    unsigned short employee_count; 
    unsigned int filesize;  
};

#pragma pack(pop)  // Restore the previous alignment

int create_new_database_file(char *filename);
int open_database_file(char *filename);
int add_database_header_information(int file_descriptor );
int verifiy_database_header_information(int file_descriptor);
int read_database_file_header(int file_descriptor, struct database_header **file_db_header);
int write_updates_to_database_file(int file_descriptor , struct database_header *db_header , struct employees *db_employees);
void read_database_file(int file_descriptor);

#endif // DATABASE_FILE_MANAGEMENT_H
