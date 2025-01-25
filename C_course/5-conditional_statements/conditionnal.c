#include <stdio.h>

int main (){
    int temp ; 
    scanf("%d" , &temp);

    if (temp >= 70){
        printf("Very HIGH temperature , Be carfull ! \n");
    }
    else if (temp < 10 ){
        printf("very LOW temperature , Be carfull \n");
    }
    else {
        printf("Good temperature\n");
    }
}