/*

Daniel Aldridge
CPE 448
Project1

client part2

accepts 2 arguments 
localhost port#

compiled using

g++ -o client2 client_p2.c

run using

./client2

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


#define MAX_LINE 256				//buffer size


using namespace std;

int main(int argc, char *argv[]){

	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	char buf[MAX_LINE];
	int s;
	socklen_t len;
    int SERVER_PORT = atoi(argv[2]);		//grab port #


	if(argc == 3){			//same as in part 1
		host = argv[1];
	}
	else{
		fprintf(stderr, "usage: simplex-talk host\n");
		exit(1);
	}


	hp = gethostbyname(host);		//set host name as localhost from command line argument
	if(!hp){
		fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
		exit(1);
	}
	//set up address data structure
	memset((char *)&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	memcpy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port = htons(SERVER_PORT);

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("simplex-talk: socket");
		exit(1);
	}

	if(connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0 ){
		perror("simplex-talk: connect");
		close(s);
		exit(1);
	}
	cout << "Connected successfully to server on port: "<<SERVER_PORT<< endl;			//show what port we connected to
	// main loop
	while(1){
		cout << "\nClient Message:";		//pad
		fgets(buf, sizeof(buf), stdin);		//grab from keyboard input	
		buf[MAX_LINE-1] = '\0';
		len = strlen(buf) + 1;
		send(s, buf, len, 0);				//send to server
        len = recv(s, buf, sizeof(buf), 0);		//recieve echoed message
        cout << "Message Echoed back from Server: "<<buf<<endl;			//print out echoed message
	}
}
