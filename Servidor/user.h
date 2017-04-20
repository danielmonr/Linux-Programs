#pragma once

#include <stdlib.h>
#include <iostream>
#include "helpers.h"
#include "../lib/textHelper.h"

struct user{
  std::string name;
  int fd;
  int id;
  char* bufferI;
  char* bufferO;
};
typedef struct user user_t;

user_t* User(std::string n, int fd, int buff_size, int id){
  user_t* user = (user_t*)malloc(sizeof(user_t));
  user->name = n;
  user->id = id;
  user->fd = fd;
  user->bufferI = (char*) malloc(buff_size);
  user->bufferO = (char*) malloc(buff_size);
  return user;
}

void deleteUser(user_t* u){
  free(u->bufferI);
  free(u->bufferO);
  free(u);
}
