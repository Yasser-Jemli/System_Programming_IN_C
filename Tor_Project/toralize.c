/* Toralize Project : */
// toralize.c 

//#include <stdio.h>
#include "toralize.h"



/* 

./toralize 1.2.3.4 80 

*/

int main(int argc,char *argv[]){
    char *host;
    int port;

    int (argc < 3){
        fprintf(stderr , "Usage: %s <host> <port> \n" , arv[0]);

        return -1 ;
    }

    host = argv[1];
    port = atoi(argv[2]);

}
