#pragma once

#include <iostream>
#include <string.h>

void errorM(std::string m){
  std::cout << "\033[1;31mError: \033[0m";
  std::cout << "\033[31m" << m << "\033[0m\n";
}

void debugM(std::string m){
  std::cout << "\033[1;33mDebug:\033[0m";
  std::cout << "\033[33m " << m << "\033[0m\n";
}

void importantM(std::string m){
  std::cout << "\033[1m" << m << "\033[0m\n";
}
