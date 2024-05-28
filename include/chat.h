#ifndef CHAT_h
#define CHAT_h

#define MAX_CLIENTS 4
#define BUFFER_SIZE 1024

//utility typedefs
#define true 1
#define false 0
#define byte unsigned char

typedef struct
{
    int pipe_fd[2];
} Client;

void start_server();
void start_client();

#endif