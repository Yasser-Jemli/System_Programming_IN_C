#include <stdio.h>

union my_union{
    int x ; 
    char y ; 
    short z ;
};
int main(){
    union my_union my ; 
    my.x = 0x11224455 ; 
    printf("%hx %hhx \n" , my.z , my.y);
}