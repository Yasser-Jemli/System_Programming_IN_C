#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libnotify/notify.h>


#define ETH_INTERFACE "enp4s0"  // Specify your Ethernet interface here

// Function to check if Ethernet cable is plugged in
int is_eth_cable_plugged(const char *interface) {
    char path[256];
    snprintf(path, sizeof(path), "/sys/class/net/%s/carrier", interface);

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    char result[2];
    ssize_t bytes_read = read(fd, result, sizeof(result));
    close(fd);

    if (bytes_read < 1) {
        return -1;
    }

    return (result[0] == '1') ? 1 : 0;  // '1' means plugged in, '0' means unplugged
}

// Function to check internet access
int has_internet_access() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return 0;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(53);  // DNS port
    inet_pton(AF_INET, "8.8.8.8", &server.sin_addr);  // Google's public DNS server

    // Attempt to connect
    int ret = connect(sock, (struct sockaddr *)&server, sizeof(server));
    close(sock);

    return (ret == 0);  // Return 1 if connection succeeded, 0 otherwise
}

// Function to send notification (replaced with console output)
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
        sleep(1);  // Check every 5 seconds
    }

    return 0;
}