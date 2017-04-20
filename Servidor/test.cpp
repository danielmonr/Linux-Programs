#include "helpers.h"
#include "./Protocols/messages.h"
#include "server.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	/*server_t* se = Server(8000, "0.0.0.0", 250);
	cout << "hello" << endl;
	
	StartServer(se, 5);
	
	
	CloseServer(se);*/
	
	char* buffer = (char*)malloc(255);
	string m = "mensaje de prueba";
	message_t* testm1 = Message(PRIVATE, m, 1, 3);
	CreateBuffedMessage(testm1, buffer);
	message_t* testm2 = Message(buffer);
	
	return 0;
}