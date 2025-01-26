#include <stdio.h>

// something is wrong here :(


// what are we doing here 

// we're taking two pointors to variables a  , b 
// then we are swaipping the variables in the scope of the function 
//     In the swap function, a and b are pointers to the original variables x and y in main.

// However, when you do a = b and b = temp, 
// you're only changing the local pointers a and b within the function. The original values x and y in main remain unchanged.
int swap( int *a, int *b) {
    int *temp = a; // temp = 10 
    printf("temp value is %d \n" , *temp);
    a = b; // a equel 20 
    printf("the value of a is %d \n" , *a);
    b = temp; // b equal 10 
    printf("The value of b is %d \n" , *b);
}

// Solution : To swap the values, you need to dereference the pointers and modify the actual values they point to.

int swap_correct (int *a , int *b){
    int temp = *a ; 
    *a = *b ;
    *b = temp ;
}

int main() {
    int x = 10, y = 20;
    printf("values order before swapping a : %d || b : %d\n", x, y);
    swap(&x, &y);
    printf("values order after swappping - (bad swap) a : %d || b : %d\n", x, y);
    swap_correct(&x,&y);
    printf("values order after swappping - (correct swap) a : %d || b : %d\n", x, y);

    return 0;
}