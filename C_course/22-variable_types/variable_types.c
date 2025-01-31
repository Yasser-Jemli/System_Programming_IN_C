#include <stdio.h>

int main ( int argc , char *argv[]){
    int x ; 
    char y ; // 1 byte , 8 bits 
    short s ; // 2 bytes , 16 bits 
    int i ; // 4 bytes , 32 bits 
    long long int l ; // 8 byte , 64 bit 

    int xx = -4 ; 
    /*
    for char we have 4 is like 00000100 

    what a compiler will do is that he take the first bit to check if it's negative or positive 

    so is the value is signed you're limiting the representation of that type in our case it will be from -128 to 127 

    while in unsigned type it will be from 0 to 255 
    */

   /*
   Character values of type unsigned char have a range from 0 to 0xFF hexadecimal. 
   A signed char has range 0x80 to 0x7F. 
   These ranges translate to 0 to 255 decimal, and -128 to +127 decimal, respectively. 
   The /J compiler option changes the default from signed to unsigned .
   */
    unsigned int xx = 4 ; 

    float f = 3.14 ; 

    double d = 3.14159 ;

    // size_t // it's an alias of another type ( as an example )
}