#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "chat_server.h"

void start_server() {
    int server_fd, client_fd;
    char buffer[BUFFER_SIZE];
    ClientInfo client_info;

    // Remove any existing server FIFO and create a new one
    unlink(SERVER_PATH);
    if (mkfifo(SERVER_PATH, 0666) == -1) {
        perror("Failed to create server FIFO");
        exit(1);
    }

    printf("Server started. Waiting for clients...\n");

    // Open the server FIFO for reading and writing
    server_fd = open(SERVER_PATH, O_RDWR);
    if (server_fd == -1) {
        perror("Failed to open server FIFO");
        unlink(SERVER_PATH);
        exit(1);
    }

    while (1) {
        // Read client information from the server FIFO
        if (read(server_fd, &client_info, sizeof(ClientInfo)) == -1) {
            perror("Failed to read from server FIFO");
            continue;
        }

        // Open the client FIFO for reading and writing
        client_fd = open(client_info.fifo_name, O_RDWR);
        if (client_fd == -1) {
            perror("Failed to open client FIFO");
            continue;
        }

        while (1) {
            // Read message from the client
            if (read(client_fd, buffer, BUFFER_SIZE) == -1) {
                perror("Failed to read from client FIFO");
                break;
            }
            printf("Received from client %d: %s\n", client_info.client_id, buffer);

            // Send response to the client
            snprintf(buffer, BUFFER_SIZE, "Echo from server: %s", buffer);
            if (write(client_fd, buffer, strlen(buffer) + 1) == -1) {
                perror("Failed to write to client FIFO");
                break;
            }
        }

        close(client_fd);
    }

    close(server_fd);
    unlink(SERVER_PATH);
}
