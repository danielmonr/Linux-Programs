#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define TCP_PORT 8000
#define BUFF_SIZE 250

using namespace std;

int client_id;

int main(int argc, char* argv[]){

    if(argc < 2 || argc > 3){
        cout << "Wrong number of arguments" << endl;
        return 0;
    }


    char buffer[BUFF_SIZE];
    struct sockaddr_in sock;


    client_id = socket(PF_INET, SOCK_STREAM, 0);
    sock.sin_port = htons(TCP_PORT);
    sock.sin_family = AF_INET;
    inet_aton(argv[1], &sock.sin_addr);
    
    int state = connect(client_id, (struct sockaddr *) &sock, sizeof(sock));

    if (state == 0){
        cout << "Connected to " << inet_ntoa(sock.sin_addr) << ":" << ntohs(sock.sin_port) << endl;

        while(read(fileno(stdin), buffer, sizeof(buffer))){
            cout << buffer << endl;
        }
    }
    else{
        cout << "Failed to connect!" << endl;
        close(client_id);
        return 0;
    }

    close(client_id);

    return 0;
}
