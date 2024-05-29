#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "chat_server.h"

void start_server()
{
    int server_fd, client_fd;
    char buffer[BUFFER_SIZE];
    ClientInfo client_info;

    // Create the server file
    if (mkfifo(SERVER_path, 0666) == -1)
    {
        perror("Server file creation Error!\n");
        exit(111);
    }

    printf("Server started. Waiting for clients...\n");

    // Open the server file for reading
    server_fd = open(SERVER_path, O_RDONLY);
    if (server_fd == -1)
    {
        perror("Server fd Error!\n");
        exit(222);
    }

    while (1)
    {
        // Read client information from the server file
        if (read(server_fd, &client_info, sizeof(ClientInfo)) == -1)
        {
            perror("Reading error!\n");
            continue;
        }

        // Open the client server file for writing
        client_fd = open(client_info.fifo_name, O_WRONLY);
        if (client_fd == -1)
        {
            perror("Client side Error!\n");
            continue;
        }

        // Send a message to the client
        snprintf(buffer, BUFFER_SIZE, "Hello, client %d!", client_info.client_id);
        if (write(client_fd, buffer, strlen(buffer) + 1) == -1)
        {
            perror("Writing Error!\n");
        }

        close(client_fd);
    }

    close(server_fd);
    unlink(SERVER_path);
}
