#ifndef GLOBAL_H
#define GLOBAL_H

#include<vector>
#include<queue>
#include <pthread.h>
#include "request.h"
#include "clock.h"
#include "sync_priority_queue.h"
#include "sync_queue.h"
#include "sync_map.h"


extern sync_priority_queue <client_request*, std::vector<client_request*>, client_request_comp> request_pq;
extern pthread_t server_handler;


extern unsigned int my_id;
extern unsigned int num_client;
extern int *client_sockets;
extern my_clock clk; 

extern sync_queue<server_message *> server_queue;
extern sync_queue<pending_request *> pending_queue;
extern sync_map pending_map;
extern struct sockaddr_in serv_addr;


#endif