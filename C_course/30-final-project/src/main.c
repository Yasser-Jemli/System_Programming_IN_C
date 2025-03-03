#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"

int print_usage(char *argv[]){
    printf("Usage : %s -n -f <databasefile>\n", argv[0]);
    printf("\t -n - create new database file \n");
    printf("\t -f - (required) path to database file\n");
    return 0 ;
}

int main(int argc , char *argv[]){
    char *filepath = NULL ;
    bool newfile = false;
    bool list = false;
    int c;
    int dbfd = -1 ;
    struct dbheader_t *dbhdr = NULL ;
    struct employees_t *employees = NULL ;
    char *addstring ; 

    while ((c = getopt(argc , argv , "nf:a:l")) != -1){
        switch(c){
            case 'n':
                newfile=true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case 'a':
                addstring = optarg;
                break;
            case '?':
                printf("Unkown option -%c\n" , c);
                break;
            default:
                return -1;
        }
    }

    if(filepath == NULL){
        printf("Filepath is a required arguement \n");
        print_usage(argv);
    }

    if (newfile){
        dbfd = create_db_file(filepath);
        if (dbfd == STATUS_ERROR){
            printf("Unable to create database file \n");
            return STATUS_ERROR;
        }

        if (create_db_header(dbfd , &dbhdr) == STATUS_ERROR){
            printf("Failed to create database header \n");
            return -1 ; 
        }
    } else {
        dbfd = open_db_file(filepath);
        if(dbfd == STATUS_ERROR){
            printf("Unable to open database file \n");
            return -1 ;
        }

        if(validate_db_header(dbfd , &dbhdr ) == STATUS_ERROR){
            printf("Failed to validate database header \n");
            return -1 ;
        }
    } 
    if ( read_employees(dbfd , dbhdr , &employees) != STATUS_SUCCESS ) {
        printf ("Failed to read employees \n");
        return -1 ; 
    }
    if ( addstring ){
        dbhdr->count++;
        employees = realloc(employees, dbhdr->count*(sizeof(struct employee_t)));
        add_employee(dbhdr , employees , addstring);
    }

    printf("Newfile: %d\n" , newfile);
    printf("Filepath: %s\n" , filepath);

    if(list){
        list_employees(dbhdr , employees);
    }
    output_file(dbfd,dbhdr);
    return 0;
}