#include <stdio.h>
#include <errno.h>  // For errno
#include <string.h> // For strerror()

int main() {
    const char *filename = "nonexistent_file.txt";

    // Attempt to open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Print the error message
        printf("Error: %s\n", strerror(errno));
    } else {
        printf("File opened successfully.\n");
        fclose(file);
    }

    return 0;
}