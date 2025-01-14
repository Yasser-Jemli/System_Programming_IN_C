#include <stdio.h>


int main (){
    // our string 
    char string[] = "hello";
    // printf("%c" , *string);
    // int length = strlen(string);
    // printf("%d", length);
    // length variable
    int count = 0;

    // using while loop 
    while (string[count] != '\0') {
        count++;
    }

    printf("%d" , count);
}