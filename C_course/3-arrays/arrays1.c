#include <stdio.h>


#define ARRAY_SIZE  10
int main (){

    // declare an array of 10 integers 
    int array[ARRAY_SIZE] ; 
    // set the fourth element to 2 ( so the fourth element will have index 3 since in arrays we start with index 0 )

    array[3] = 2 ; 

    printf("%d\n",array[3]);


    // just for fine let's see the index 9 what has as a value 

    printf("%d\n",array[9]); // are we always having 0 ?  it seems yes 


}