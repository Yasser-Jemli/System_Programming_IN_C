#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
    int fd = open("./i_don't_existe.txt", O_RDONLY);
    if ( fd == -1 ){
        perror("Issue in Open Function" );
        return -1;
    }
}