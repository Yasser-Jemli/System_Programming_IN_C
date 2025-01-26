#include <stdio.h>


// functions Syntaxe 
/*

return_type function_name(arguments or parametres){
}

*/

/* to make an addition of two given integers , x & y , and return the result */
int add(int x , int y){
    int z = x + y ; 
    return z ;
}

int main (int argc , char * argv[]){

    int other_int = add(5 , 6);
    printf("%d\n", other_int);

    return 0 ; 

}