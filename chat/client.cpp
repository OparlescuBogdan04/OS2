#include "chat.h"
#include <ctime>

std::string client_name;

void receive_messages(SOCKET sock)
{
    char buffer[1024];
    int bytesReceived;
    while ((bytesReceived = recv(sock, buffer, 1024, 0)) > 0)
    {
        buffer[bytesReceived] = '\0';
        std::cout << buffer << std::endl;
    }
}

std::string current_time()
{
    std::time_t now = std::time(nullptr);
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "(%H:%M:%S)", std::localtime(&now));
    return std::string(time_str);
}

int main()
{

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    std::cout << "Enter your name: ";
    // std::cin >> client_name;
    std::getline(std::cin, client_name);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    connect(sock, (sockaddr *)&server, sizeof(server));

    std::thread(receive_messages, sock).detach();
    std::string msg;
    while (true)
    {
        std::getline(std::cin, msg);
        msg = "<" + client_name + ">" + current_time() + ":" + msg;
        send(sock, msg.c_str(), (int)msg.size(), 0);
    }

    closesocket(sock);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;

}
