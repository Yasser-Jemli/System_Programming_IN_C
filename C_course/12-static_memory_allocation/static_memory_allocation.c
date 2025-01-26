#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX_EMPLOYEE 1000


struct employe {
    int id ;
    int income ; 
    bool staff; 
};


int initilize_employe(struct employe *e){
    static int numEmployees = 0 ;
    numEmployees++;
    e->id = numEmployees ; 
    e->income = 5 ;
    e->staff = false ; 

    return numEmployees;
}

int main (int argc , char **argv[]){
    int n = 4 ;
    struct employe *employees = malloc(sizeof(struct employe)*n);
    if (employees == NULL){
        printf("allocator failed ! \n");
        return -1;  
    }

    for (int i=0 ; i < n ; i++){
        int id = initilize_employe(&employees[i]);
        printf("New employee ID is %d \n" , id);
    }

    initilize_employe(&employees[0]);
    printf("%d\n" , employees[0].income);
    free(employees);
    employees = NULL ; 

}