#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include "chat.h"

#define SERVER_FIFO "server_fifo"
#define CLIENT_FIFO_TEMPLATE "client_fifo_%d"
#define CLIENT_FIFO_NAME_LEN 64

void start_client();

#endif // CHAT_CLIENT_H
