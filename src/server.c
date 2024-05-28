#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "chat.h"

void start_server()
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe Error!\n");
        exit(999); //server error
    }

    printf("Server started!\nWaiting for clients...\n\n");

    while (1)
    {
        byte buffer[BUFFER_SIZE];
        int bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            perror("Reading Error!\n");
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            exit(EXIT_FAILURE);
        }

        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
}
