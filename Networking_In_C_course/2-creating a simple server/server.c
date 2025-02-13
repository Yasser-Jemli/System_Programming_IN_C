#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc , char *argv[]){

    struct sockaddr_in serverInfo = {0};
    struct sockaddr_in clientInfo = {0};
    int clientSize = 0 ;

    serverInfo.sin_family  = AF_INET ;
    serverInfo.sin_addr.s_addr = 0 ;
    serverInfo.sin_port = htons(5556); 
    
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("Socket");
        return fd ;
    }

    // bind 
    if (bind(fd,(struct sockaddr* )&serverInfo , sizeof(serverInfo)) == -1 ){
        perror("bind");
        close(fd);
        return -1 ; 
    }

    // listen 
    if ( listen (fd , 0 ) == -1){
        perror("listen");
        close(fd);
        return -1 ; 
    }

    // accept
    int cfd = accept(fd , (struct sockaddr *)&clientInfo , &clientSize);
    if (cfd == -1 ){
        perror("accept");
        close(fd);
        return -1 ; 
    }

    close(cfd);

}