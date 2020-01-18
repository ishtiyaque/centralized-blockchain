#include <stdio.h>
//#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include<unistd.h>
#include<strings.h>
#include <arpa/inet.h>
#include <stdlib.h>

enum message_type{transfer, balance};