#include <stdio.h>
#include <gnu/libc-version.h>

int main() {
    // Get the GNU C library version
    const char *version = gnu_get_libc_version();

    // Print the version
    printf("GNU C Library (glibc) version: %s\n", version);

    return 0;
}
