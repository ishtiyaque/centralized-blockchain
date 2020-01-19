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

typedef unsigned int Clientid;

enum message_type{transfer, balance};


#endif