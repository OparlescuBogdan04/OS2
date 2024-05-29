#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "chat_client.h"

void start_client() {
    int server_fd, client_fd;
    char buffer[BUFFER_SIZE];
    ClientInfo client_info;
    char client_fifo[CLIENT_MAX_NAME_LEN];

    // Create a unique name for the client FIFO
    snprintf(client_fifo, CLIENT_MAX_NAME_LEN, "/tmp/client_%d", getpid());

    // Create the client FIFO
    if (mkfifo(client_fifo, 0666) == -1) {
        perror("Failed to create client FIFO");
        exit(1);
    }

    // Open the server FIFO for writing
    server_fd = open(SERVER_PATH, O_WRONLY);
    if (server_fd == -1) {
        perror("Failed to open server FIFO");
        unlink(client_fifo);
        exit(1);
    }

    // Send client information to the server
    client_info.client_id = getpid();
    strncpy(client_info.fifo_name, client_fifo, CLIENT_MAX_NAME_LEN);
    if (write(server_fd, &client_info, sizeof(ClientInfo)) == -1) {
        perror("Failed to write to server FIFO");
        close(server_fd);
        unlink(client_fifo);
        exit(1);
    }

    // Open the client FIFO for reading and writing
    client_fd = open(client_fifo, O_RDWR);
    if (client_fd == -1) {
        perror("Failed to open client FIFO");
        close(server_fd);
        unlink(client_fifo);
        exit(1);
    }

    // Chat loop
    while (1) {
        // Read user input
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        // Send message to the server
        if (write(server_fd, buffer, strlen(buffer) + 1) == -1) {
            perror("Failed to write to server FIFO");
            break;
        }

        // Read server response
        if (read(client_fd, buffer, BUFFER_SIZE) == -1) {
            perror("Failed to read from client FIFO");
            break;
        }
        printf("Server: %s\n", buffer);
    }

    close(client_fd);
    close(server_fd);
    unlink(client_fifo);
}
