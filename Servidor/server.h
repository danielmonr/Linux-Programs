#include "stdlib.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>


struct server{
    char* buffer;
    struct sockaddr_in address;
    struct sockaddr_in cli_addr;
    int sock;
    socklen_t size_socket;
    bool active;
};
typedef struct server server_t;

server_t* Server(int port, char* address, int buff_size){
    // Create server instance
    server_t* serv = (server_t*)malloc(sizeof(server_t));
    // Create server's global buffer
    serv->buffer = (char*) malloc(buff_size);

    // inicialize socket
    serv->sock = socket(PF_INET, SOCK_STREAM, 0);
    // Link socket with an address and port
    serv->address.sin_port = htons(port);
    serv->address.sin_family = AF_INET;
    inet_aton(address, &(serv->address).sin_addr);
    bind(serv->sock, (struct sockaddr *) &(serv->address), sizeof(serv->address));
    serv->size_socket = sizeof(serv->address);
    serv->active = false;

    return serv;
}

void StartServer(server_t* se, int max_cli){
    listen(se->sock, max_cli);
    se->active = true;
}

void CloseServer(server_t* s){
    s->active = false;
    close(s->sock);
    free(s->buffer);
    free(s);
}
