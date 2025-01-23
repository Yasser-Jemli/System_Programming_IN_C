#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>



void printing_Hello(char * msg){
    fprintf(stdout ,"%s\n", msg);
}

int main() {
    printing_Hello("Hello From My tty Reading programme");
    printf("$ Enter something: >>> $ ");
    fflush(stdout);
    char buffer[100];
    
    int tty_fd = open("/dev/tty", O_RDWR);
    if (tty_fd < 0) {
        perror("open");
        return 1;
    }

    
    ssize_t bytes_read = read(tty_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("You entered: %s\n", buffer);
    }

    close(tty_fd);
    return 0;
}