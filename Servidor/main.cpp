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
#include <pthread.h>
#include <semaphore.h>
#include "helpers.h"
#include "server.h"

#define BUFF_SIZE 250

#define TCP_PORT 8000
#define MAX_CLI 3

using namespace std;

sem_t connections;
server_t* se;

void* manageConnections(dlist_t*);

int main(int argc, char* argv[]){

    if(argc != 2){
        errorM("Please insert the ip address for the server. (x.x.x.x)");
        return 0;
    }
    pthread_t conn_mgr;
    sem_init(&connections, 0, MAX_CLI);

    //cout << "Main Process PID: " << ::getpid() << endl;

    // Server Block
    se = Server(TCP_PORT, argv[1], BUFF_SIZE); // Create server
	  StartServer(se, MAX_CLI); // Inicilize server
    dlist_t* clients = DList(); // Double linked List for clients ids
    if(pthread_create(&conn_mgr, 0, (void*(*)(void*))manageConnections, (void*)clients)){ // Accept connections through another thread
      errorM("Not possible to create thread.");
      return -1;
    }
    pthread_join(conn_mgr, NULL);
    CloseServer(se); // Close server and clean memory
    // End of ser	printf("El filosofo %d se levanta de la mesa.\n", info);
}

void* manageConnections(dlist_t* clients){
  debugM("manageConnections");
    int client;
    while(se->active){
      sem_wait(&connections);
      client = accept(se->sock, (struct sockaddr *) &(se->cli_addr), &(se->size_socket));
      addNode(clients, client);
      cout << "New connection from: " << inet_ntoa(se->cli_addr.sin_addr) << endl;
    }
    pthread_exit(0);
}

void destroyConnection(dlist_t* l, int val){
  debugM("destroying connection");
  deleteAt(l,search(l,val));
  sem_post(&connections);
}
