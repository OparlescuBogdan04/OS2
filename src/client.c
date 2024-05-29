#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "chat_client.h"

void start_client()
{
    int server_fd, client_fd;
    char buffer[BUFFER_SIZE];
    ClientInfo client_info;
    char client_fifo[CLIENT_MAX_NAME_LEN];

    // Create a unique name for the client
    snprintf(client_fifo, CLIENT_MAX_NAME_LEN, "client:%d", getpid());

    // Create the client server file
    if (mkfifo(client_fifo, 0666) == -1)
    {
        perror("Server file creation Error!\n");
        exit(111);
    }

    // Open server file for writing
    server_fd = open(SERVER_path, O_WRONLY);
    if (server_fd == -1)
    {
        perror("Server fd Error!\n");
        unlink(client_fifo);
        exit(222);
    }

    // Send client information to the server
    client_info.client_id = getpid();
    strncpy(client_info.fifo_name, client_fifo, CLIENT_MAX_NAME_LEN);
    if (write(server_fd, &client_info, sizeof(ClientInfo)) == -1)
    {
        perror("Writing Error!\n");
        close(server_fd);
        unlink(client_fifo);
        exit(333);
    }

    // Open the client server file for reading
    client_fd = open(client_fifo, O_RDONLY);
    if (client_fd == -1)
    {
        perror("Client Error!\n");
        close(server_fd);
        unlink(client_fifo);
        exit(444);
    }

    // Read and print the message from the server
    if (read(client_fd, buffer, BUFFER_SIZE) == -1)
    {
        perror("Reading Error!\n");
    }
    else
    {
        printf("Received: %s\n", buffer);
    }

    close(client_fd);
    close(server_fd);
    unlink(client_fifo);
}
