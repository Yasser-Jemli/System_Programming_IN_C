#include <stdio.h>
#include <stdlib.h> // For atoi()

int main() {
    const char *input = "123abc";

    // Convert the string to an integer
    int number = atoi(input);

    // atoi() does not provide error handling
    printf("Converted number: %d\n", number);

    return 0;
}