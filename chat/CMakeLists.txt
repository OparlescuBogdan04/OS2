cmake_minimum_required(VERSION 3.10)
project(TerminalChat)

if(WIN32)
    set(SOCKET_LIBS ws2_32)
else()
    set(SOCKET_LIBS pthread)
endif()

add_executable(client client.cpp)
target_link_libraries(client ${SOCKET_LIBS})

add_executable(server server.cpp)
target_link_libraries(server ${SOCKET_LIBS})
