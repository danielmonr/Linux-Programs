#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>
#include "../../lib/textHelper.h"
#include "../server.h"

typedef enum {ERROR, SYSTEM, PRIVATE, GLOBAL} messageType;

struct message{
	std::string mess;
	messageType type;
	int sender;
	int receiver;
	
};
typedef struct message message_t;

/* 
* private message : /p[idsender]-[idreceiver]|[message]
* global message : /g[idsender]|[message]
* system message : /s[idsender]-[idreceiver]|[message]
*/

void setPrivateMessage(message_t* m, char* buffer){
	char term = '|';
	char sep = '-';
	std::string str(buffer);
	m->mess = str.substr(str.find_first_of(term,2)+1);
	std::string re = str.substr(str.find_first_of(sep,2)+1, str.find_first_of(term,3)-str.find_first_of(sep,2)-1);
	debugM("re = " + re);
	std::string sen = str.substr(2, str.find_first_of(sep,2)-2);
	debugM("sen = " + sen);
	m->receiver = std::stoi(re);
	m->sender = std::stoi(sen);
	debugM("Message: " + m->mess);
	debugM("Type: "+std::to_string(m->type));
}

void setGlobalMessage(message_t* m, char* buffer){
	char term = '|';
	std::string str(buffer);
	m->mess = str.substr(str.find_first_of(term,2)+1);
	std::string sen = str.substr(2, str.find_first_of(term,2)-2);
	debugM("sen = " + sen);
	m->sender = std::stoi(sen);
	debugM("Message: " + m->mess);
	debugM("Type: "+std::to_string(m->type));
}

void setSystemMessage(message_t* m, char* buffer){
	char term = '|';
	char sep = '-';
	std::string str(buffer);
	m->mess = str.substr(str.find_first_of(term,2)+1);
	std::string re = str.substr(str.find_first_of(sep,2)+1, str.find_first_of(term,3)-str.find_first_of(sep,2)-1);
	debugM("re = " + re);
	std::string sen = str.substr(2, str.find_first_of(sep,2)-2);
	debugM("sen = " + sen);
	m->receiver = std::stoi(re);
	m->sender = std::stoi(sen);
	debugM("Message: " + m->mess);
	debugM("Type: "+std::to_string(m->type));
}

void CreateBuffedMessage(message_t* m, char* buffer){
	std::string res = "/";
	switch (m->type){
		case SYSTEM:
			res+= "s"+std::to_string(m->sender)+"-"+std::to_string(m->receiver)+"|"+m->mess;
			break;
		case GLOBAL:
			res+= "g"+std::to_string(m->sender)+"|"+m->mess;
			break;
		case ERROR:
			break;
		case PRIVATE:
			res+= "p"+std::to_string(m->sender)+"-"+std::to_string(m->receiver)+"|"+m->mess;
			break;
		default:
			break;
	}
	debugM("string buffer: " + res);
	strcpy(buffer, res.c_str());
}

message_t* Message(messageType t, std::string m, int s, int r){
	message_t* mess = (message_t*)malloc(sizeof(message_t));
	mess->type = t;
	mess->mess = m;
	mess->sender = s;
	mess->receiver = r;
	return mess;
}

message_t* Message(char* buffer){
	message_t* mess = (message_t*)malloc(sizeof(message_t));
	char prefix[3];
	memcpy(prefix, buffer, 2);
	prefix[2] = '\0';
	switch (prefix[1]){
		case 's':
			mess->type = SYSTEM;
			setSystemMessage(mess, buffer);
			break;
		case 'g':
			mess->type = GLOBAL;
			setGlobalMessage(mess, buffer);
			break;
		case 'p':
			mess->type = PRIVATE;
			setPrivateMessage(mess, buffer);
			break;
		default:
			errorM("Prefix not recognized");
			mess->type = ERROR;
			break;
	}
	debugM("Prefix: " + std::string(prefix));
	debugM("Sender: " + std::to_string(mess->sender));
	debugM("Receiver: " + std::to_string(mess->receiver));
	return mess;
}

void DeleteMessage(message_t* m){
	free(m);
}