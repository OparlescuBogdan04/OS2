#ifndef CHAT_H
#define CHAT_H

#define BUFFER_SIZE 1024
#define SERVER_PATH "server"
#define CLIENT_MAX_NAME_LEN 64

typedef struct
{
    int client_id;
    char fifo_name[CLIENT_MAX_NAME_LEN];
} ClientInfo;

void start_server();
void start_client();

#endif
