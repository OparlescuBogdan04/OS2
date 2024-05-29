#ifndef CHAT_h
#define CHAT_h

#define byte unsigned char
#define BUFFER_SIZE 1024

#define SERVER_path "server"
#define CLIENT_MAX_NAME_LEN 64


typedef struct
{
    int pipe_fd[2];
} Client;

void start_server();
void start_client();

#endif