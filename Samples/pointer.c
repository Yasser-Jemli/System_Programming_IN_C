#include <stdio.h>
#include <string.h>

int main (){

    char str[32];
    char *p ;
    strncpy(str, "I like apples" , 31 );
    p = str ; 
    p = p + 1 ; // p++
    printf("%s\n" , p);
    printf("%c\n" ,*p);
    return 0 ;
}