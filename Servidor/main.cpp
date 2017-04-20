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
#include "./Protocols/messages.h"
#include "chatMessages.h"

#define BUFF_SIZE 250

#define TCP_PORT 8000
#define MAX_CLI 3

using namespace std;


server_t* se;

void* manageConnections();
void createUser(int, int);
void* receiver(void*);
void* sender(void*);

int main(int argc, char* argv[]){

    if(argc != 2){
        errorM("Please insert the ip address for the server. (x.x.x.x)");
        return 0;
    }
    pthread_t conn_mgr;

    //cout << "Main Process PID: " << ::getpid() << endl;

    // Server Block
    se = Server(TCP_PORT, argv[1], BUFF_SIZE); // Create server
	  StartServer(se, MAX_CLI); // Inicilize server
    //dlist_t* clients = DList(); // Double linked List for clients ids
    if(pthread_create(&conn_mgr, 0, (void*(*)(void*))manageConnections, NULL)){ // Accept connections through another thread
      errorM("Not possible to create thread.");
      return -1;
    }
    pthread_join(conn_mgr, NULL);
    CloseServer(se); // Close server and clean memory
    // End of ser	printf("El filosofo %d se levanta de la mesa.\n", info);
}

void* manageConnections(){
  int cont = 1;
  debugM("manageConnections");
    int client;
    while(se->active){
      sem_wait(&(se->connections));
      client = accept(se->sock, (struct sockaddr *) &(se->cli_addr), &(se->size_socket));
      createUser(client,cont);
      cont++;
      cout << "New connection from: " << inet_ntoa(se->cli_addr.sin_addr) << endl;
    }
    pthread_exit(0);
}

void createUser(int fd, int num){
  string tempname = "guest"+num;
  user_t* u = User(tempname, fd, BUFF_SIZE, num);
  int it = addUser(se, u);
  if(it < 0 || pthread_create(&(se->threadsI[it]),0,(void*(*)(void*))receiver, (void*)u)){
    errorM("Couldn't create input thread (user: "+tempname+").");
  }
}

message_t* evalInput(char* in){
  string input(in);
  if(in[0] == '@'){
    debugM("Private Message");
    int re = searchUser(se, input.substr(1, input.find_first_of(' ')-1));
    debugM("Receiver: " + to_string(re));
  }
}

void* receiver(void* u){
  user_t* user = (user_t*)u;
  message_t* m;
  int readN;
  while(u && (readN = read(user->fd, user->bufferI, BUFF_SIZE))){
    cout << (user->bufferI) << endl;
    m = Message(user->bufferI);
    receivedMessage(se, m, user);
  }

}

void* sender(void* u){
  user_t* user = (user_t*)u;
}
