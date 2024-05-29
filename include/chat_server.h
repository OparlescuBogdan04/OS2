#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include "chat.h"

typedef struct {
    int client_id;
    char fifo_name[CLIENT_FIFO_NAME_LEN];
} ClientInfo;

void start_server();

#endif
