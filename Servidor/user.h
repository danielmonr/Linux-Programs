#pragma once

#include <stdlib.h>
#include <iostream>
#include "helpers.h"
#include "../lib/textHelper.h"

struct user{
  std::string name;
  node_t* node;
  char* bufferI;
  char* bufferO;
};
typedef struct user user_t;

user_t* User(std::string n, node_t* node, int buff_size){
  user_t* user = (user_t*)malloc(sizeof(user_t));
  user->name = n;
  user->node = node;
  user->bufferI = (char*) malloc(buff_size);
  user->bufferO = (char*) malloc(buff_size);
  return user;
}

void deleteUser(user_t* u){
  free(u->bufferI);
  free(u->bufferO);
  free(u);
}
