#include <stdio.h>
#include <string.h>
#include "../include/chat_client.h"
#include "../include/chat_server.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("Usage: %s <option>\n", argv[0]);
        perror("options:\n'server' or '1'\n'client' or '2'\n\n");
        return 1;
    }

    if (strcmp(argv[1], "server") == 0 || strcmp(argv[1], "1") == 0)
    {
        start_server();
        return 0;
    }

    if (strcmp(argv[1], "client") == 0 || strcmp(argv[1], "2") == 0)
    {
        start_client();
        return 0;
    }

    perror("Unknown option: %s\n", argv[1]);
    return 1;
}
