#include <stdio.h>

int main() {
    int x = 10;
    int *p = &x;    // Pointer to x
    int **pp = &p;  // Pointer to pointer p

    printf("Value of x: %d\n", x);       // Output: 10
    printf("Value of *p: %d\n", *p);     // Output: 10
    printf("Value of **pp: %d\n", **pp); // Output: 10

    printf("Address of x: %p\n", (void *)&x); // Address of x
    printf("Value of p: %p\n", (void *)p);    // Address stored in p (same as &x)
    printf("Value of *pp: %p\n", (void *)*pp); // Address stored in p (same as &x)
    printf("Address of p: %p\n", (void *)&p);  // Address of p
    printf("Value of pp: %p\n", (void *)pp);   // Address stored in pp (same as &p)
    printf("Address of pp : %p\n" , (void *)&pp);

    return 0;

    /*
    Key Points

    A pointer to a pointer (int **) stores the address of another pointer (int *).

    Use double pointers for:

        Dynamic memory allocation (e.g., 2D arrays).

        Modifying pointers in functions.

        Working with arrays of strings.

        Implementing data structures like linked lists or trees.

        Returning multiple values from functions.
    */
}