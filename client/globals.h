#ifndef GLOBAL_H
#define GLOBAL_H

#include<vector>
#include<queue>
#include <pthread.h>
#include "request.h"

extern priority_queue <client_request*, vector<client_request*>, client_request_comp> req_q; 
extern pthread_t server_handler;
extern pthread_mutex_t mut_server;
extern pthread_mutex_t mut_time;


extern unsigned int my_id;
extern unsigned int my_time; 


#endif