#include <stdio.h>

#define MAX_PERSONNE 1024

// #define DEBUG


int main (){
    #ifdef DEBUG
    printf("WE ARE IN DEBUG MODE : %s : %d \n" , __FILE__ , __LINE__);
    #endif

    printf("Normall Massage in %s in %d \n", __FILE__ , __LINE__);
    return 0 ; 
}