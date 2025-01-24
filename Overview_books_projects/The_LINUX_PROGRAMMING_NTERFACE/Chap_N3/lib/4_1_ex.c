#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define DEFAULT_PERMISSIONS 0644

// Signal handler function for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("\nReceived SIGINT (Ctrl+C). Exiting gracefully...\n");
    exit(EXIT_SUCCESS); // Exit the program gracefully
}

int main(int argc, char* argv[]) {
    // Register the signal handler for SIGINT (Ctrl+C)
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Error: Failed to set up signal handler");
        exit(EXIT_FAILURE);
    }

    int appendMode = 0; // Flag for append mode
    int opt;
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                appendMode = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] file\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Check if a file argument is provided
    if (optind >= argc) {
        fprintf(stderr, "Error: No output file specified.\n");
        fprintf(stderr, "Usage: %s [-a] file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* filename = argv[optind];

    // Open the output file
    int flags = O_WRONLY | O_CREAT;
    if (appendMode) {
        flags |= O_APPEND; // Append to the file if it exists
    } else {
        flags |= O_TRUNC; // Overwrite the file if it exists
    }

    int fd = open(filename, flags, DEFAULT_PERMISSIONS);
    if (fd == -1) {
        perror("Error: Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Read from standard input and write to both standard output and the file
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        // Write to standard output
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error: Failed to write to standard output");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Write to the file
        if (write(fd, buffer, bytesRead) != bytesRead) {
            perror("Error: Failed to write to file");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead == -1) {
        perror("Error: Failed to read from standard input");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Clean up
    close(fd);
    return 0;
}