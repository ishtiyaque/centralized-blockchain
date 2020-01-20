#include "utils.h"
#include "request.h"

#include "sync_priority_queue.h"
#include "sync_queue.h"
#include "clock.h"
#include "server_handler.h"

sync_priority_queue <client_request*, vector<client_request*>, client_request_comp> client_pq;
pthread_t server_handler;

sync_queue<server_message *> server_queue;
int num_client;

struct sockaddr_in serv_addr;

unsigned int my_id;
my_clock clk; 

int *client_sockets;

int main(int argc, char *argv[]) {
	char command[5];
	Clientid rcvr;
	double amount;
	server_message *msg;
		
	if(argc < 2) {
		printf("Missing Client id. Exiting...\n");
		exit(1);
	}
	my_id = atoi(argv[1]);
	init("../config.txt");
	
	
	while(1) {
		scanf("%s",command);
		if(!strcmp(command,"BAL")) {
			msg = new server_message;
			msg->type = balance;
			msg->sndr = my_id;
			server_queue.push(msg);
		} else if(!strcmp(command,"SEND")) {
			msg = new server_message;
			msg->type = transfer;
			msg->sndr = my_id;
			scanf("%d",&(msg->rcvr));
			scanf("%lf",&(msg->amount));
			server_queue.push(msg);
		} else {
			printf("Invalid command");
		}
	}
	
	return 0;
}
