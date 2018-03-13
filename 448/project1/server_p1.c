/*

Daniel Aldridge
CPE 448
Project1

server part1

accepts 1 arguments 
 port#

compiled using

g++ -o server1 client_p1.c

run using

./server1

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


#define MAX_PENDING 5				//max number of pending connections
#define MAX_LINE 256				//buff size

using namespace std;


int main(int argc, char *argv[]){

	struct sockaddr_in sin;
	char buf[MAX_LINE];			//buffer
	socklen_t len;
	int s, new_s;
	int client_num = 1;			//client num that increments
	int SERVER_PORT = atoi(argv[1]);
	/*build address data structure */
	memset((char*)&sin,0,sizeof(sin)); //use memset instead of bzero
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);		//grab port #

	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){		//setup waiting open
		perror("simplex-talk: socket");
		exit(1);
	}
	cout << "socket created.." << endl;		//socket is created
	if((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0 ){
		perror("simplex-talk: bind");
		exit(1);
	}
	listen(s, MAX_PENDING);

	cout <<"Listening to connections on port: "<<SERVER_PORT<<endl;		//what port are we listening on 

	while(1){
		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("simplex-talk: accept");					//connection not accepected
			exit(1);
		}
		else
			cout << "Client: "<<client_num<<" connected..." << endl;		//we are connected
		
		while( len = recv(new_s, buf, sizeof(buf), 0))
			cout << "Msg Rec. from Client: "<<client_num<<" "<<buf<<endl;		//print out what client we received msg from
	 close(new_s);			//close the connection
	 cout << "Client: "<<client_num<<" connection ended..." << endl;			//print out connection message
	 client_num += 1;			//incrememnt client counter
	}

}