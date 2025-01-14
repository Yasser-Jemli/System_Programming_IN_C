#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Conditional DEBUG macro (can be controlled at compile-time)
#ifdef DEBUG
    #define log_debug(msg) printf("[DEBUG] %s\n", msg)
#else
    #define log_debug(msg) // No-op when DEBUG is not defined
#endif

int main(int argc, char* argv[]) {
    // Check if the "debug" argument is provided at runtime
    if (argc > 1 && strcmp(argv[1], "debug") == 0) {
        // Enable debugging at runtime
        printf("Debug mode enabled at runtime.\n");
        #ifdef DEBUG
            // Now the macro will be active if DEBUG is defined at compile-time
            log_debug("Debugging is active");
        #else
            printf("DEBUG macro is not defined at compile-time.\n");
        #endif
    } else {
        printf("Debug mode disabled.\n");
    }

    // Main logic of the program
    printf("Running the main logic of the program...\n");

    // Example usage of the debug log function
    log_debug("Performing an operation...");

    return 0;
}
