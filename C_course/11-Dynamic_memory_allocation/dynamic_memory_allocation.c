#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX_EMPLOYEE 1000
struct employe {
    int id ;
    int income ; 
    bool staff; 
};


void initilize_employe(struct employe *e){
    e->id = 0 ; 
    e->income = 5 ;
    e->staff = false ; 

    return;
}

int main (int argc , char **argv[]){
    int n = 4 ;
    struct employe *employees = malloc(sizeof(struct employe)*n);
    if (employees == NULL){
        printf("allocator failed ! \n");
        return -1;  
    }

    initilize_employe(&employees[0]);
    printf("%d\n" , employees[0].income);
    free(employees);
    employees = NULL ; 


    // A good to know is valgirnd is a tool that helps see your memory issue in your code 
    // so it may be a good way to check your own code before merging ut using valgrind tool 
}