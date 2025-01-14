#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if_arp.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long int int64;


struct s_mac{
    int64 addr:48;
};

typedef struct s_mac Mac ;

bool chmac(int8* , Mac);

Mac generatemac(void);
int main(int , char**);

Mac generatemac (){
    int64 a , b ;
    Mac mac ; 
    a = (long)random();
    b = (long)random();
    /*
    The code is essentially generating a 48-bit number by multiplying a and b, 
    and then using the modulus operation to ensure it fits within the MAC address range (0 to 2^48 - 1). 
    This ensures the value is compatible with the expected format for a MAC address.
    */
    mac.addr = ((a * b) % 281474976710656);
    return mac ; 
}

bool chmac(int8 *If , Mac mac){
    struct sockaddr *p;
    struct ifreq ir;
   // int8 *If;

    int fd , ret;
    int8 *addr;
    int16 size ;

    char *_ = "";
    fd= socket(AF_INET,SOCK_DGRAM, IPPROTO_IP);
    assert(fd > 0);

    size = sizeof(struct sockaddr) + (int16)strlen(addr) + 1 ;
    p = (struct sockaddr *)malloc(size);
    assert(p);

    strncpy(ir.ifr_ifrn.ifrn_name, (char *)If , (IF_NAMESIZE-1));
    p -> sa_family = ARPHRD_ETHER;
    strncpy(p -> sa_data, (char*)addr ,(size+1));
    ir.ifr_ifru.ifru_hwaddr.sa_family = ARPHRD_ETHER ;
    ir.ifr_ifru.ifru_hwaddr = p ;
    ret = ioctl(fd , SIOCSIFHWADDR , ir);
    free(p);
    close(fd);
    return (!ret)?
    true:
    false;
}

int main(int argc , char *argv[]){
    Mac mac ;
    int8 *If;

    if (argc < 2 ){
        fprintf(stderr,"Usage : %s INTERFACE\n", *argv);
        return -1 ;
    }
    else{
        If = (int8 *)argv[1];
        (void)If;
    }
    srand(getpid());
    mac =generatemac();
    printf("0x%llxv \n", (long long)mac.addr);
    return 0 ;
}
