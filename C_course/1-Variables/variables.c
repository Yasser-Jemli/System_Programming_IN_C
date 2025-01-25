#include <stdio.h>

int g_Numpersonnes = 0 ; 

void some_other_functions(){
    
    int personnID = 0 ; 

}

int main (){
    // variables declaration 
    // type var_name = intial_value ; 
    int personnID = 0 ; 
    // we can use expression to initilize variable 
    int personn2ID = personnID + 1 ;

    // Create Scope that can handle scope variables 
    {
        int presonnID = 0 ; 

        presonnID += 1 ;  
    }
}