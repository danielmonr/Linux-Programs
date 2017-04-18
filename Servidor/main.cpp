/*
 * ========================================================================
 *
 *
 *       Filename: main.cpp
 *
 *       Description: Program that creates a server that can handle 
 *                    multiple connections.
 *
 *       Version: 1.0
 *       Created: 19/01/17
 *       Revision: none
 *       Compiler: g++
 *
 *       Author: Daniel Monzalvo, danielmonr@gmail.com
 *
 * ========================================================================
*/

#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "helpers.h"

#define BUFF_SIZE 250

#define TCP_PORT 8000
#define MAX_CLI 3

int server, client;

using namespace std;


int main(int argc, char* argv[]){

    dlist_t* clients = DList();

    cout << "Main Process PID: " << ::getpid() << endl;

    char* buffer_global = (char*) malloc (BUFF_SIZE);

    // Server initialization
    struct sockaddr_in address;
    struct sockaddr_in cli_addr;

    // Create server
    server = socket(PF_INET, SOCK_STREAM, 0);

    // Link socket with an address and port
    address.sin_port = htons(TCP_PORT);
    address.sin_family = AF_INET;
    inet_aton(argv[1], &address.sin_addr);
    bind(server, (struct sockaddr *) &address, sizeof(address));

    // Start listening for clients
    listen(server, MAX_CLI);

    // Inicialize socket length variable
    socklen_t size_socket = sizeof(address);

    int num_clients = 0;
    while(num_clients < MAX_CLI){
        client = accept(server, (struct sockaddr *) &cli_addr, &size_socket);

        cout << "New connection from: " << inet_ntoa(cli_addr.sin_addr) << endl;

        num_clients++;
    }


    close(server);
    free (buffer_global);

    return 1;
}
