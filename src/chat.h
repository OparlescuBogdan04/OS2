#ifndef chat_guard
#define chat_guard
#include "utility.h"

#define MAX_CLIENTS 4
#define BUFFER_SIZE 1024

typedef struct
{
    int pipe_fd[2];
} Client;

void start_server();
void start_client();

#endif