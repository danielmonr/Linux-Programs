#include "helpers.h"
#include "server.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	server_t* se = Server(8000, "0.0.0.0", 250);
	cout << "hello" << endl;
	
	StartServer(se, 5);
	
	
	CloseServer(se);
	
	return 0;
}