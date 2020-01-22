#include "utils.h"
#include "request.h"

#include "sync_priority_queue.h"
#include "sync_queue.h"
#include "clock.h"
#include "server_handler.h"
#include "dispatcher.h"
#include "client_receiver.h"

sync_priority_queue <client_request*, vector<client_request*>, client_request_comp> request_pq;
pthread_t server_handler;
pthread_t dispatcher;
pthread_t *client_handler;

sync_queue<server_message *> server_queue;
sync_queue<pending_request *> pending_queue;
sync_map pending_map;

unsigned int num_client;

struct sockaddr_in serv_addr;

unsigned int my_id;
my_clock clk; 

int *client_sockets;

int main(int argc, char *argv[]) {
	char command[5];
	Clientid rcvr;
	double amount;
	pending_request *req;
		
	if(argc < 2) {
		printf("Missing Client id. Exiting...\n");
		exit(1);
	}
	my_id = atoi(argv[1]);
	init("../config.txt");
	
	pthread_create(&dispatcher, 0, dispatch, 0);
	client_handler = new pthread_t[num_client - 1];
	for(int i = 0; i < num_client - 1; i++) {
		pthread_create(client_handler + i, 0, handle_client, &(client_sockets[i]));
	}
	
	while(1) {
		scanf("%s",command);
		if(!strcmp(command,"BAL")) {
			req = new pending_request(balance, 0, 0);
			pending_queue.push(req);
		} else if(!strcmp(command,"SEND")) {
			scanf("%d",&rcvr);
			scanf("%lf",&amount);
			req = new pending_request(transfer, rcvr, amount);						
			pending_queue.push(req);
		} else {
			printf("Invalid command");
		}
	}
	
	return 0;
}
