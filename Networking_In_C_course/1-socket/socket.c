#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int main(){
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("Socket");
        return fd ;
    }


    printf("my fd is : %d\n",fd);  
}