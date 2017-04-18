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
    int* clients;
    socklen_t size_socket;
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
    
    return serv;
}

void StartServer(server_t* se, int max_cli){
    listen(se->sock, max_cli);
    se->clients = (int*) malloc(max_cli*sizeof(int));
    int num_clients = 0;
    while(num_clients < max_cli){
        se->clients[num_clients] = accept(se->sock, (struct sockaddr *) &(se->cli_addr), &(se->size_socket));

        std::cout << "New connection from: " << inet_ntoa(se->cli_addr.sin_addr) << std::endl;

        num_clients++;
    }
}

void CloseServer(server_t* s){
    close(s->sock);
    free(s->buffer);
    free(s->clients);
    free(s);
}