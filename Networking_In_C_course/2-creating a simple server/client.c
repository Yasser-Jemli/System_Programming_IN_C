#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>


typedef enum {
    PROTO_HELLO,

} proto_type_e ; 

typedef struct {
    proto_type_e type ;
    unsigned short len;

} proto_hdr_t ; 

ssize_t

void handle_client(int fd){
    char buf[4096] = {0};
    proto_hdr_t *hdr = buf ; 
    hdr->type = htonl(PROTO_HELLO) ; 
    hdr->len = sizeof(int) ;
    int reallen = hdr->len ; 
    hdr->len = htons(hdr->len);


    int *data = (int*)hdr[1];
    *data = htonl(1) ;

    write(fd , hdr , sizeof(proto_hdr_t) + reallen);
}

int main(int argc , char *argv[]){

    if(argc != 2){
        printf("Usage : %s <ip of the host> \n" , argv[0]);
        return 0 ; 
    }

    struct sockaddr_in serverInfo = {0};

    serverInfo.sin_family  = AF_INET ;
    serverInfo.sin_addr.s_addr = inet_addr(argv[1]);
    serverInfo.sin_port = htons(5556); 
    
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("Socket");
        return fd ;
    }

    while(1){
        if (connect (fd , (struct sockaddr*)&serverInfo , sizeof(serverInfo)) == -1){
        perror("Connect");
        close (fd);
        return -1 ; 
        }
    }

    close(fd);

}