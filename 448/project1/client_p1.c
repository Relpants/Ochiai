/*

Daniel Aldridge
CPE 448
Project1

client part1

accepts 2 arguments 
localhost port#

compiled using

g++ -o client1 client_p1.c

run using

./client1

*/



#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <fstream>


#define MAX_LINE 256						//buffer size


using namespace std;

int main(int argc, char *argv[]){

	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	char buf[MAX_LINE];		//buffer 
	int s;
	socklen_t len;
	int SERVER_PORT = atoi(argv[2]);		//get port number from command line and convert to integer


	if(argc == 3){					//passing two arguments
		host = argv[1];				//set host to be localhost
	}
	else{							
		fprintf(stderr, "usage: simplex-talk host\n");
		exit(1);		//exit
	}


	hp = gethostbyname(host);		//set hostname
	if(!hp){				//verify
		fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
		exit(1);		//exit
	}
	//build address data structure
	memset((char *)&sin, 0, sizeof(sin));		//change to memset from bzero
	sin.sin_family = AF_INET;
	memcpy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);		//change to memcpy from bcopy
	sin.sin_port = htons(SERVER_PORT);		//grab port #

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("simplex-talk: socket");
		exit(1);
	}

	if(connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0){			//connect to server
		perror("simplex-talk: connect");				
		close(s);							//close socket
		exit(1);							//exit program
	}
	cout << "Connected successfully to server on port: "<<SERVER_PORT<< endl;		//show what port we connected on
	// main loop below
	while(1){			//keep looping
		cout << "\nClient Message:";		//add begin msg part
		fgets(buf, sizeof(buf), stdin);		//get text from keyboard input
		buf[MAX_LINE-1] = '\0';				//buf will terminate with 'enter'
		len = strlen(buf) + 1;				//set length
		send(s, buf, len, 0);				//send to server
	}
}
