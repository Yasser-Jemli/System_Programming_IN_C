#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int own_cd(char **args)
{
    // If no arguments are passed, change to the home directory
    if (args[1] == NULL) {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
        if (chdir(home) != 0) {
            perror("cd");
        }
    }
    // If a directory is provided, change to that directory
    else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
    return 1;
}

int own_env(char **args)
{
    (void)args;  // We mark args as unused for now to avoid compiler warnings
    
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
    return 1;
}

int own_help(char **args)
{
    (void)args;  // We mark args as unused for now to avoid compiler warnings

    printf("Welcome to the custom shell!\n");
    printf("Available commands:\n");
    printf("  cd [directory]  : Change the current directory to the specified directory.\n");
    printf("  env             : Display the current environment variables.\n");
    printf("  help            : Show this help message.\n");
    printf("  exit            : Exit the shell.\n");
    return 1;
}

int own_exit(char **args)
{
    (void)args;  // We mark args as unused for now to avoid compiler warnings

    printf("Exiting shell...\n");
    exit(0);
}
