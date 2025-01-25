#include <stdio.h>


#define MAX_IDS 32
int main (){
    // type of array , name , the size of elements
    // int ids[MAX_IDS];

    // or we can not declare the size but decalre the elements of it 

    int ids [] = { 1, 2 , 3};

    // access a value of an array 

    printf("%d\n" , ids[0]);
}