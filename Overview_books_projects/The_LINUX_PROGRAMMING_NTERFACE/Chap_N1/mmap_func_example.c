#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FILEPATH "/tmp/mmapped.bin"
#define NUMINTS  (1000)
#define FILESIZE (NUMINTS * sizeof(int))

int main(int argc, char *argv[])
{
    int i;
    int fd;
    int result;
    int *map;  /* mmapped array of int's */

    /* Open a file for writing.
     *  - Creating the file if it doesn't exist.
     *  - Truncating it to 0 size if it already exists. (not really needed)
     *
     * Note: "O_WRONLY" mode is not sufficient when mmaping.
     */
    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
	perror("Error opening file for writing");
	exit(EXIT_FAILURE);
    }

    /* Stretch the file size to the size of the (mmapped) array of ints
     */
    result = lseek(fd, FILESIZE-1, SEEK_SET);
    if (result == -1) {
	close(fd);
	perror("Error calling lseek() to 'stretch' the file");
	exit(EXIT_FAILURE);
    }
    
    /* Something needs to be written at the end of the file to
     * have the file actually have the new size.
     * Just writing an empty string at the current file position will do.
     *
     * Note:
     *  - The current position in the file is at the end of the stretched 
     *    file due to the call to lseek().
     *  - An empty string is actually a single '\0' character, so a zero-byte
     *    will be written at the last byte of the file.
     */
    result = write(fd, "", 1);
    if (result != 1) {
	close(fd);
	perror("Error writing last byte of the file");
	exit(EXIT_FAILURE);
    }

    /* Now the file is ready to be mmapped.
     */
    map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
	close(fd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }
    
    /* Now write int's to the file as if it were memory (an array of ints).
     */
    for (i = 1; i <=NUMINTS; ++i) {
	map[i] = 2 * i; 
    }

    /* Don't forget to free the mmapped memory
     */
    if (munmap(map, FILESIZE) == -1) {
	perror("Error un-mmapping the file");
	/* Decide here whether to close(fd) and exit() or not. Depends... */
    }

    /* Un-mmaping doesn't close the file, so we still need to do that.
     */
    close(fd);
    return 0;
}

/*

The program creates or modifies the file /tmp/mmapped.bin. To verify:

Check File Size

The file size should match FILESIZE (e.g., 1000 integers * 4 bytes = 4000 bytes on a typical system):

ls -l /tmp/mmapped.bin


The program writes integers (e.g., 2, 4, 6, ...) into the file. 

Use the hexdump or od command to inspect the binary file's contents:

od -An -t d4 /tmp/mmapped.bin

or

hexdump -v -e '4/4 "%d "' /tmp/mmapped.bin

These commands will display the integers stored in the file.



*/


// Explanation of MMAP and when to Use it 

/*

The mmap system call is used to map files or devices into memory, creating a memory region that directly corresponds to the contents of the file or device. This allows programs to interact with files as if they are simple arrays in memory, bypassing traditional I/O functions like read and write. This approach can improve performance and simplify coding for certain tasks.

Memory-Mapped File Access:

Maps a file directly into the program's address space.
Allows direct access to file contents via pointers, avoiding repeated system calls.


Shared Memory:

Enables multiple processes to share memory by mapping the same file.
Changes made by one process can be seen by others.

Efficient I/O:

Reduces overhead by avoiding explicit read/write calls.
The operating system manages the loading and synchronization of file content.

Why Use mmap?

Performance Gains:

For large files, mmap avoids copying data between kernel and user space.
Lazy loading only reads file content when accessed, saving memory and time.

Convenience:

Treats file content as if it were a normal array in memory.
Simplifies random access to file data.

Interprocess Communication (IPC):

Multiple processes can map the same file into memory for efficient data sharing.

How Does It Work?
Map File to Memory:

Using mmap, the kernel maps the file's contents to a region of virtual memory.
Access File as Memory:

The program can read or write to this memory region, and the kernel synchronizes these changes with the file.
Automatic Management:

The operating system handles paging, ensuring only necessary parts of the file are loaded into physical memory.

Example Use Cases
Large File Handling:

Working with large datasets (e.g., images, logs) without loading the entire file into memory.
Random Access:

Accessing specific parts of a file without seeking or buffering.
Shared Memory:

Processes sharing data through a file-backed memory region.
Efficient IPC:

Use memory mapping to share data between processes without the overhead of pipes or sockets.
Memory-Mapped Databases:

Many databases (e.g., SQLite) use mmap to map data files for faster access.


When Not to Use mmap
Small Files:

The overhead of setting up a memory-mapped file may not be worth it for small files.
Streaming Data:

mmap works best for random access, not for sequential streaming of data.
Concurrency Issues:

Concurrent writes to the same mapped region require careful synchronization.


In Summary
mmap is a powerful tool for efficient file I/O, allowing you to manipulate files as if they were arrays in memory. 
It is especially useful for large files, random access patterns, and shared memory scenarios. 
However, it requires careful handling to avoid pitfalls like segmentation faults or synchronization problems.
*/