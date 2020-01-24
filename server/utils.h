#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
//#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include<unistd.h>
#include<strings.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

//#define UDP

#ifdef UDP
	#define PROTOCOL SOCK_DGRAM
#else
	#define PROTOCOL SOCK_STREAM
#endif

typedef unsigned int Clientid;

enum message_type{transfer, balance};

struct server_message {
	message_type type;
	Clientid sndr;
	Clientid rcvr;
	double amount;
	unsigned int timestamp;
};

struct server_response {
	unsigned int timestamp;
	double amount;
};


#endif
