/*

Daniel Aldridge
CPE 448
Project1

server part2

accepts 1 arguments 
 port#

compiled using

g++ -o server2 server_p2.c

run using

./server2

*/



#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <iostream>


#define MAX_PENDING 5				//max number of connections
#define MAX_LINE 256				//buffer size

using namespace std;


int main(int argc, char *argv[]){

	struct sockaddr_in sin;
	char buf[MAX_LINE];
	socklen_t len;
	int s, new_s;
	int client_num = 1;				//client number
    int SERVER_PORT = atoi(argv[1]);			//grab server port

    //set up address data structure
	memset((char*)&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("simplex-talk: socket");
		exit(1);
	}
	cout << "socket created.." << endl;			//socket created
	if((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0 ){
		perror("simplex-talk: bind");
		exit(1);
	}
	listen(s, MAX_PENDING);
    
    cout <<"Socket created listening on port: "<<SERVER_PORT<<endl;			//show what port we are listening on

	while(1){
		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("simplex-talk: accept");
			exit(1);
		}
		else
			cout << "Client: "<<client_num<<" connected..." << endl;
		
		while(len = recv(new_s, buf, sizeof(buf), 0)){
			cout << "Msg Rec. from Client: "<<client_num<<" "<<buf;
            cout << "Echoing Msg Back to Client: "<<client_num<<endl;
            send(new_s, buf,len,0);				//grab message recieved and send or "echo" back to client
        }
	 close(new_s);			//close connection
	 cout << "Client: "<<client_num<<" connection ended..." << endl;			//print usefull message
	 client_num += 1;		//increment client number
	}

}
