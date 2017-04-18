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
#include <unistd.h>
#include <stdlib.h>
#include "helpers.h"
#include "server.h"

#define BUFF_SIZE 250

#define TCP_PORT 8000
#define MAX_CLI 3

using namespace std;



void manageConnections(server_t*, dlist_t*);

int main(int argc, char* argv[]){

    if(argc != 2){
        cout<< "Please insert the ip address for the server. (x.x.x.x)\n"
        return 1;
    }

    //cout << "Main Process PID: " << ::getpid() << endl;

    // Start server
    server_t* se = Server(TCP_PORT, argv[1], BUFF_SIZE);
	StartServer(se, MAX_CLI);

    dlist_t* clients; = DList(); // Double linked List for clients ids
    manageConnections(se, clients);

    CloseServer(se);
    return 1;
}

void manageConnections(server_t* se, dlist_t* clients){
    
    while(clients->length < MAX_CLI){
        client = accept(server, (struct sockaddr *) &cli_addr, &size_socket);

        cout << "New connection from: " << inet_ntoa(cli_addr.sin_addr) << endl;

        num_clients++;
    }
    cout << "Maximum number of connections reached\n";
}
