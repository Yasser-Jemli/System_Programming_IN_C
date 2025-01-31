#include <stdio.h>

int main (int argc , char *argv[]){

    unsigned int x = 4;

    int sx = (int)(x) ; // Casting : we are converting the x from usnigned int to int ( for this example we have casting with the same size)

    unsigned int bigx=0xfffffefe;

    short kindabig = (short)bigx; // we are casting a variable with 32 bits to 16 bits 
    // this could result in an information last since we are getting only 16 bits from the 32 bits 


    short short2= -1; // 0xffff1111
    int wassashort = (int)(short2);//0xffffffff
    // this is Casting from 16 bits to 32 bits , so we increasing the size like 

    float f =3.14;
    int wasafloat =(int)f;

    // how to go from (char *) to (short *)
    short *mydata = (short*)argv[1];
}