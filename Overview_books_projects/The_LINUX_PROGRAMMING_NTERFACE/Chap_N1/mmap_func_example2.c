#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>



/*

Kindly compile the code with gcc -Wall -g command 

*/
int main(int argc , char** argv){
    // and mmap can also be used to map files into memory!
    int fd = open("sometext.txt" ,O_RDONLY);
    struct stat sb ; 

    if (fstat(fd,&sb) == -1 )
    {
        perror("Coudln't get file size. \n");
    }

    printf("file size is %ld\n", sb.st_size);


    char *file_in_memory = mmap(NULL , sb.st_size, PROT_READ , MAP_PRIVATE , fd , 0 );

    if (file_in_memory == MAP_FAILED) {
        perror("Error mapping the file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Printing file , as an array of characters ... \n\n");

    for (int i=0 ; i < sb.st_size;i++){
        printf("%c",file_in_memory[i]);
    }

    printf("\n");


    return 0 ; 
}