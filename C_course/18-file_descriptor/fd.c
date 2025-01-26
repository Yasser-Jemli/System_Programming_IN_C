#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
    /*
    0 = stdin
    1 = stdout
    2 = stderr
    */

   /*
   
        In simple words, when you open a file, the operating system creates an entry to represent that file 
        and store the information about that opened file. 
        So if there are 100 files opened in your OS then there will be 100 entries in OS (somewhere in kernel). 
        These entries are represented by integers like (...100, 101, 102....). 
        This entry number is the file descriptor. So it is just an integer number that uniquely represents an opened file for the process. 
        If your process opens 10 files then your Process table will have 10 entries for file descriptors.

        Similarly, when you open a network socket, it is also represented by an integer and it is called Socket Descriptor.

   */

    /*
    

        A file descriptor is an opaque handle that is used in the interface between user and kernel space to identify file/socket resources. 
        Therefore, when you use open() or socket() (system calls to interface to the kernel), 
        you are given a file descriptor, 
        which is an integer (it is actually an index into the processes u structure - but that is not important). 
        Therefore, if you want to interface directly with the kernel, using system calls to read(), write(), close() etc. 
        the handle you use is a file descriptor.

        There is a layer of abstraction overlaid on the system calls, which is the stdio interface. 
        This provides more functionality/features than the basic system calls do. 
        For this interface, the opaque handle you get is a FILE*, which is returned by the fopen() call. 
        There are many many functions that use the stdio interface fprintf(), fscanf(), fclose(), which are there to make your life easier. 
        In C, stdin, stdout, and stderr are FILE*, which in UNIX respectively map to file descriptors 0, 1 and 2.

    */

    /*
    
        To the kernel, all open files are referred to by File Descriptors. A file descriptor is a non-negative number.

        When we open an existing file or create a new file, the kernel returns a file descriptor to the process. 
        The kernel maintains a table of all open file descriptors, which are in use. 
        The allotment of file descriptors is generally sequential and they are allotted to the file 
        as the next free file descriptor from the pool of free file descriptors. 
        When we closes the file, the file descriptor gets freed and is available for further allotment.
        See this image for more details :
            Link --> https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms 

        When we want to read or write a file, 
        we identify the file with the file descriptor that was returned by open() or create() function call, 
        and use it as an argument to either read() or write().
        It is by convention that, UNIX System shells associates the file descriptor 0 with Standard Input of a process, 
        file descriptor 1 with Standard Output, and file descriptor 2 with Standard Error.
        File descriptor ranges from 0 to OPEN_MAX. 
        File descriptor max value can be obtained with ulimit -n. For more information, go through 3rd chapter of APUE Book.

    
    */


}