#pragma once

#include "stdlib.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include "../lib/textHelper.h"
#include "user.h"

struct server{
    char* buffer;
    struct sockaddr_in address;
    struct sockaddr_in cli_addr;
    int sock;
    socklen_t size_socket;
    bool active;
    user_t** users;
    pthread_t* threadsI;
    pthread_t* threadsO;
    int maxusers;
    sem_t connections;
    
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
    se->maxusers = max_cli;
    sem_init(&(se->connections), 0, max_cli);
    se->users = (user_t**)malloc(max_cli*sizeof(user_t*));
    for(int i = 0; i < max_cli; ++i){
        se->users[i] = NULL;
    }
    debugM("max_cli = " + std::to_string(max_cli));
    se->threadsI = (pthread_t*)malloc(max_cli*sizeof(pthread_t));
    se->threadsO = (pthread_t*)malloc(max_cli*sizeof(pthread_t));
    listen(se->sock, max_cli);
    se->active = true;
}

void CloseServer(server_t* s){
    s->active = false;
    close(s->sock);
    free(s->buffer);
    for (int i = 0; i < s->maxusers; ++i){
        if(s->users[i] != NULL){
            deleteUser(s->users[i]);
            pthread_cancel(s->threadsI[i]);
            pthread_cancel(s->threadsO[i]);
        }
    }
    free(s->users);
    free(s->threadsI);
    free(s->threadsO);
    free(s);
}

int firstFree(server_t* s){
    int i = 0;
    debugM("maxusers = "+std::to_string(s->maxusers));
    for (i; i < s->maxusers; ++i){
        if(s->users[i] == NULL){
            debugM("Allocating user at " + std::to_string(i));
            return i;
        }
    }
    errorM("No free spaces in users array.");
    return -1;
}

int addUser(server_t* s, user_t* u){
    int it = firstFree(s);
    s->users[it] = u;
    return it;
}

void removeUser(server_t* s, user_t* u){
    int i = 0;
    for(i; i < s->maxusers;++i){
        if(u == s->users[i]){
            s->users[i] = NULL;
            deleteUser(u);
            return;
        }
    }
    errorM("User could not be removed.");
}

int searchUser(server_t* s, std::string n){
    for(int i = 0; i < s->maxusers; ++i){
        if((s->users[i] != NULL) && (s->users[i]->name == n))
            return i;
    }
    errorM("User not found");
    return -1;
}

int searchUser(server_t* s, int uid){
    for(int i = 0; i < s->maxusers; ++i){
        if((s->users[i] != NULL) && (s->users[i]->name == n))
            return i;
    }
    errorM("User not found");
    return -1;
}

void changeUserName(server_t* s, user_t* u, std::string newname){
    u->name = newname;
}