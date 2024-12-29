#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>

#define EXT_SUCCESS 0
#define EXT_ERR_TOO_FEW_ARGS 1 

int main(int argc , char** argv){
    
    char *basePath = NULL ;
    char *token = NULL ;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXT_ERR_TOO_FEW_ARGS);
    }
    // The code allocates enough memory to hold a copy of the string in argv[1], including the null terminator.
    // The allocated size is strlen(argv[1]) + 1 bytes.
    // The cast (char *) converts the void * returned by malloc to a char *
    // String in C are terminated with null terminator ( \0 ) 
    basePath = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
    strcpy(basePath , argv[1]);

    token = strtok(basePath,"/");
    while(token != NULL){
        basePath = token;
        token = strtok(NULL , "/");
    }
    
    // printf("%s\n", basePath);

    while(true){
        
    }

}
