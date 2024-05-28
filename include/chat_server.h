#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include "chat.h"

#define SERVER_FIFO "server_fifo"
#define CLIENT_FIFO_TEMPLATE "client_fifo_%d"
#define CLIENT_FIFO_NAME_LEN 64

typedef struct {
    int client_id;
    char fifo_name[CLIENT_FIFO_NAME_LEN];
} ClientInfo;

void start_server();

#endif
