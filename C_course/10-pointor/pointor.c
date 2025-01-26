#include <stdio.h>
#include <stdbool.h>

struct employe {
    int id ; 
    int income ; 
    bool staff ;
};

void initilize_employee(struct employe *e){
    e -> income =1200;
    e -> id = 2 ; 
    e -> staff = false ; 
    return ;
};

int main (){
    int x = 3 ; 
    int *pX = &x ;
    printf ("%d\n", *pX);
    printf("%p\n" , pX);
    // why we are using pointor ? 
    // 1 - Dynamic Memory Allocation 
    // 2 - Passing Large Structures to Functions
    // 3 - Modifying Function Arguments
    // 4 - Working with Arrays and Strings
    // 5 - 

    // the easy way 
    // struct employe Aziz;
    // Aziz.id = 1 ; 
    // Aziz.income = 1500 ; 
    struct employe Aziz;
    initilize_employee(&Aziz);

    printf("incomde of Aziz : %d\n" , Aziz.income);


}