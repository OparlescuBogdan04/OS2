#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "chat.h"

void start_client()
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe Error!\n");
        exit(123); //client error
    }

    printf("Successful server connection!\n");

    while (true)
    {
        byte buffer[BUFFER_SIZE];
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if (write(pipe_fd[1], buffer, strlen(buffer)) == -1)
        {
            perror("Writing Error!\n");
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            exit(EXIT_FAILURE);
        }

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
}