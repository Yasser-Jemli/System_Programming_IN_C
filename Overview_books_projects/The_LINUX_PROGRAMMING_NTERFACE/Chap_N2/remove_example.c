#include <stdio.h>
#include <errno.h>  // For errno
#include <string.h> // For strerror()

int main() {
    const char *filename = "nonexistent_file.txt";

    // Attempt to remove the file
    if (remove(filename) == -1) {
        // Print the error message
        printf("Error: %s\n", strerror(errno));
    } else {
        printf("File removed successfully.\n");
    }

    return 0;
}

// int main() {

// Create the file "file.txt" first in case you want to try this binairy with success and comment previous code 
and uncomment the below code
//     const char *filename = "file.txt";

//     // Attempt to remove the file
//     if (remove(filename) == -1) {
//         // Print the error message
//         printf("Error: %s\n", strerror(errno));
//     } else {
//         printf("File removed successfully.\n");
//     }

//     return 0;
// }