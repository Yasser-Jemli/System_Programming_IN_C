#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>

#include <sys/inotify.h>

#include <libnotify/notify.h>
#include <libnotify/notification.h>

#define EXT_SUCCESS 0
#define EXT_ERR_TOO_FEW_ARGS 1 
#define EXT_ERR_INIT_INOTIFY 2
#define EXT_ERR_ADD_WATCH 3  
#define EXT_ERR_BASE_PATH_NULL 4
#define EXT_ERR_READ_INOTIFY 5 
#define EXT_ERR_INIT_LIBNOTIFY 6  

int IeventQueue = -1;
int IeventStatus = -1;

char *ProgramTitle = "Watchdog";

void signal_handler(int signal){
    int closeStatus =-1;
    printf ("Signal received , cleaning up ..... \n");
    closeStatus = inotify_rm_watch(IeventQueue , IeventStatus);
    if ( closeStatus == -1 ){
        fprintf(stderr , "Error removing from watch queue!\n");
    }
    close(IeventQueue);
    exit(EXIT_SUCCESS);
}

int main(int argc , char** argv){
    
    bool libnotifyInitStatus = false ;

    char *basePath = NULL;
    char *token = NULL;
    char *notificationMessage = NULL ;
    
    NotifyNotification *notifyHandle;

    char buffer[4096];
    int readLength ;

    const struct inotify_event* watchEvent; 
    
    const uint32_t watchMask = IN_CREATE | IN_DELETE | IN_ACCESS | IN_CLOSE_WRITE | IN_MODIFY | IN_MOVE_SELF ; 

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXT_ERR_TOO_FEW_ARGS);
    }
    // The code allocates enough memory to hold a copy of the string in argv[1], including the null terminator.
    // The allocated size is strlen(argv[1]) + 1 bytes.
    // The cast (char *) converts the void * returned by malloc to a char *
    // String in C are terminated with null terminator ( \0 ) 
    basePath = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
    strcpy(basePath , argv[1]);

    token = strtok(basePath,"/");
    while(token != NULL){
        basePath = token;
        token = strtok(NULL , "/");
    }

    if (basePath == NULL){
        fprintf(stderr, "Error getting base path : \n");
        exit(EXT_ERR_BASE_PATH_NULL);
    }
    
    libnotifyInitStatus = notify_init(ProgramTitle);
    if (! libnotifyInitStatus){
        fprintf(stderr , "Error initializing libnotify: \n");
        exit(EXT_ERR_INIT_LIBNOTIFY);
    }
    // printf("%s\n", basePath);
    IeventQueue = inotify_init();
    
    if (IeventQueue == -1 ){
        fprintf(stderr, "Error initialising inotify instance ! \n");
        exit(EXT_ERR_INIT_INOTIFY);
    } 

    IeventStatus = inotify_add_watch(IeventQueue , argv[1] , watchMask);
    
    if (IeventStatus == -1 ){
        fprintf(stderr , "Error adding file to watch instance ! \n");
        exit(EXT_ERR_ADD_WATCH);
    }

    signal(SIGABRT , signal_handler);
    signal(SIGINT  , signal_handler);
    signal(SIGTERM , signal_handler);

    while(true){
        printf("Waiting for ievent ...\n");

        if (readLength == -1){
           fprintf(stderr , "Error reading from inotify instance!\n");
           exit(EXT_ERR_READ_INOTIFY); 
        }

        readLength = read(IeventQueue , buffer , sizeof(buffer));
        for (char  *bufferPointer = buffer ; bufferPointer < buffer + readLength ; bufferPointer += sizeof(struct inotify_event) + watchEvent-> len)
        {
            notificationMessage = NULL ;
            watchEvent = (const struct inotify_event *) bufferPointer ;

            if (watchEvent-> mask & IN_CREATE){
                notificationMessage = "File created.\n";
            }

            if (watchEvent->mask & IN_DELETE)
            {
                notificationMessage = "File Deleted.\n";
            }

            if (watchEvent->mask & IN_ACCESS){
                notificationMessage = "File accessed .\n";
            }

            if (watchEvent->mask & IN_CLOSE_WRITE){
                notificationMessage = "File written and closed . \n";
            }

            if (watchEvent->mask & IN_MODIFY){
                notificationMessage = "File modified. \n";
            }

            if (watchEvent->mask & IN_MOVE_SELF){
                notificationMessage = "File moved.\n";
            }

            if (notificationMessage == NULL){
                continue;
            }

            notifyHandle = notify_notification_new(basePath , notificationMessage , "dialog-information");
            if (notifyHandle == NULL){
                fprintf(stderr , "Notification handle was null \n");
                continue ;
            }

            notify_notification_show(notifyHandle ,NULL);
            // printf("%s\n", notificationMessage);

        }
    }

}
