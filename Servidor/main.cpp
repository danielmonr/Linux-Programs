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

user_t *users[MAX_CLI];

void* manageConnections(dlist_t*);
void createUser(node_t*, int);
void* receiver(void*);
void* sender(void*);

int main(int argc, char* argv[]){

    if(argc != 2){
        errorM("Please insert the ip address for the server. (x.x.x.x)");
        return 0;
    }
    pthread_t conn_mgr;
    sem_init(&connections, 0, MAX_CLI);
    for(int i = 0; i < MAX_CLI; ++i){
      users[i] = NULL;
    }

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
  int cont = 1;
  debugM("manageConnections");
    int client;
    while(se->active){
      sem_wait(&connections);
      client = accept(se->sock, (struct sockaddr *) &(se->cli_addr), &(se->size_socket));
      createUser(addNode(clients, client),cont);
      cont++;
      cout << "New connection from: " << inet_ntoa(se->cli_addr.sin_addr) << endl;
    }
    pthread_exit(0);
}

void createUser(node_t* no, int num){
  string tempname = "guest"+num;
  user_t* u = User(tempname, no, BUFF_SIZE);
  int it = addUser(se, u);
  if(it < 0 || pthread_create(&(se->threadsI[it]),0,(void*(*)(void*))receiver, (void*)u)){
    errorM("Couldn't create input thread (user: "+tempname+").");
  }

}

void* receiver(void* u){
  user_t* user = (user_t*)u;
  int readN;
  while(readN = read(user->node->val, user->bufferI, BUFF_SIZE)){
    cout << (user->bufferI) << endl;
  }
}

void* sender(void* u){
  user_t* user = (user_t*)u;
}

void destroyConnection(dlist_t* l, int val){
  debugM("destroying connection");
  deleteAt(l,search(l,val));
  sem_post(&connections);
}
