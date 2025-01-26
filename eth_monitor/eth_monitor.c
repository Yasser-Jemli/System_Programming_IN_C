#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <libnotify/notify.h>

#define ETH_INTERFACE "enp4s0"  // Specify your Ethernet interface here

// Function to check if Ethernet cable is plugged in
int is_eth_cable_plugged(const char *interface) {
    char command[256];
    snprintf(command, sizeof(command), "ethtool %s | grep 'Link detected' | awk '{print $3}'", interface);
    FILE *fp = popen(command, "r");
    if (!fp) {
        perror("popen");
        return -1;
    }
    char result[10];
    if (fgets(result, sizeof(result), fp)) {
        if (strncmp(result, "yes", 3) == 0)
            return 1;  // Cable is plugged in
    }
    return 0;  // Cable is unplugged
}

// Function to check internet access
int has_internet_access() {
    FILE *fp = popen("ping -c 1 8.8.8.8 > /dev/null 2>&1", "r");
    if (fp == NULL) {
        perror("ping");
        return 0;
    }
    int status = pclose(fp);
    return (status == 0);
}

// Function to send notification
void send_notification(const char *title, const char *message) {
    if (!notify_is_initted()) {
        notify_init("Ethernet Monitor");
    }
    NotifyNotification *notification = notify_notification_new(title, message, NULL);
    notify_notification_show(notification, NULL);
    g_object_unref(G_OBJECT(notification));
}

int main() {
    int eth_status = -1;
    int internet_status = -1;

    while (1) {
        int current_eth_status = is_eth_cable_plugged(ETH_INTERFACE);
        int current_internet_status = has_internet_access();

        // If the Ethernet cable status changes, notify
        if (current_eth_status != eth_status) {
            eth_status = current_eth_status;
            if (eth_status == 1) {
                send_notification("Ethernet Connected", "Ethernet cable is plugged in.");
            } else {
                send_notification("Ethernet Disconnected", "Ethernet cable is unplugged.");
            }
        }

        // If internet access status changes, notify
        if (current_internet_status != internet_status) {
            internet_status = current_internet_status;
            if (internet_status == 1) {
                send_notification("Internet Access", "Internet is accessible.");
            } else {
                send_notification("No Internet", "No internet access detected.");
            }
        }

        // Wait for a while before checking again
        sleep(5);  // Check every 5 seconds
    }

    return 0;
}
