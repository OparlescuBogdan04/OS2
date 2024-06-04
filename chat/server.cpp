#include "chat.h"

std::vector<SOCKET> clients;
std::mutex clients_mutex;

void handle_client(SOCKET client_sock)
{
    char buffer[1024];
    int bytesReceived;
    while ((bytesReceived = recv(client_sock, buffer, 1024, 0)) > 0)
    {
        buffer[bytesReceived] = '\0';
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (SOCKET client : clients)
        {
            if (client != client_sock)
                send(client, buffer, bytesReceived, 0);
        }
    }
    closesocket(client_sock);
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(std::remove(clients.begin(), clients.end(), client_sock), clients.end());
}

int main()
{

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    SOCKET listener = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(listener, (sockaddr *)&server, sizeof(server));
    listen(listener, 5);
    while (true)
    {
        SOCKET client = accept(listener, NULL, NULL);
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.push_back(client);
        std::thread(handle_client, client).detach();
    }

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
    
}
