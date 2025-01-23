#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int tty_fd = open("/dev/tty", O_WRONLY);
    if (tty_fd < 0) {
        perror("open");
        return 1;
    }

    const char *message = "Hello, terminal! i' m writing to you this message just to test /dev/tty \n";
    write(tty_fd, message, strlen(message));

    close(tty_fd);
    return 0;
}