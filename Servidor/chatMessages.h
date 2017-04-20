#pragma once

#include "./Protocols/messages.h"
#include "user.h"
#include "server.h"
#include <iostream>

void destroyConnection(server_t* se, user_t *u){
  debugM("destroying connection");
  removeUser(se, u);
  sem_post(&(se->connections));
  pthread_exit(0);
}

void processSystemMessage(server_t* se, message_t* m, user_t* u){
	//debugM("Size of mess: " + std::to_string(m->mess.length()));
	if(!m->mess.compare("endc")){
		debugM("Disconnect message");
		std::cout << "User " << u->name << " connection termination request.\n";
		destroyConnection(se, u);
	}
	else{
		debugM("Message is: " + m->mess);
	}
}

void receivedMessage(server_t* se, message_t* m, user_t* u){
	switch(m->type){
		case SYSTEM:
			debugM("Received SYSTEM MESSAGE... Proecssing");
			processSystemMessage(se, m, u);
			break;
		case PRIVATE:
			break;
		case GLOBAL:
			break;
		case ERROR:
			break;
	}
}
