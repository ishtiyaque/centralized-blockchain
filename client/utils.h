#ifndef UTILS_H
#define UTILS_H

#define SLEEP_TIME 3

#include <stdio.h>
//#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<vector>
#include<queue>
#include <pthread.h>
#include<time.h>
#include "request.h"
using namespace std;


void init(char *filename);
int broadcast(const client_message *msg);
void release_me();
void my_sleep();
#endif
