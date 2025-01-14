#include <stdio.h>

int main(){
    int x ; 
    printf("choose between 1. appeles, 2. pears or 3. bananas \n");
    scanf("%d",&x);

    switch(x){
        case 1 : /* appeles*/
        printf("Appeles \n");
        break;
        case 2 :
        printf("Pears \n");
        break;
        case 3 :
        printf("Bananas \n");
        break;
        default:
        printf("somehting eelse \n");
    }
    return 0 ;
}