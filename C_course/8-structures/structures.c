#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_EMPLOYESS 64

// avoid padding for this struct : 
    //      What does __attribute__((__packed__)) do? 
    //      When you apply the __attribute__((__packed__)) directive to a structure, you instruct the compiler to disable this padding. 
    //      This means:

    //      The compiler will not insert any padding bytes between the structure's members.
    //      The structure will be packed tightly, and its size will be the sum of the sizes of its individual members.
__attribute__((__packed__)) struct employe_t{
    int id ;
    char firstname[64];
    char lastname[64];
    float income ;
    bool ismanager;
};

int main (){
    struct employe_t aziz ; 
    strcpy(aziz.firstname , "Aziz");
    strcpy(aziz.lastname , "Bouslimi");
    // aziz.firstname = "Aziz";
    aziz.id = 1 ; 
    // aziz.lastname = "Bouslimi";
    printf("%s , %s , %d \n" , aziz.firstname , aziz.lastname , aziz.id);
    

    struct employe_t my_employees[MAX_EMPLOYESS];

    int i = 0 ; 
    for (i ; i < MAX_EMPLOYESS ; i++){
        my_employees[i].id = i ;

        /*In C, string literals like "name" are pointers to the first character of the string. 
        When you add an integer (i) to the string pointer ("name" + i), it advances the pointer by i positions. 
        This results in a pointer to the substring starting from the i-th character of "name" (for example, "name" + 1 gives "ame"), 
        which is not what you want.*/
        
        // @DEPRECATED Code
        // strcpy(my_employees[i].firstname , "name" + i );
        
        sprintf(my_employees[i].firstname, "name%d", i);
        my_employees[i].ismanager = false ;

        printf("%s , %d , %d \n" , my_employees[i].firstname , my_employees[i].ismanager , aziz.id);
    }


    printf("the size of employee structure is : %ld\n" , sizeof(struct employe_t));
}