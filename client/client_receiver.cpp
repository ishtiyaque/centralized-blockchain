#include "client_receiver.h"
#include<stdio.h>
#include<stdlib.h>

void *handle_client(void *sock) {
	int *socket = (int *)sock;
	int n;
	printf("Thread created with value %d\n",*socket);
	client_message msg;
	client_request *req;
	client_message response;
	server_message* ser_msg;
	pending_request * pen_req;
	while(1) {
		bzero((char *) &msg, sizeof(msg));
		n = read(*socket, &msg, sizeof(msg));
		if(n < 0) {
			printf("read error. Exiting....\n");
			exit(1);
		}
		printf("Read from socket %d\n",*socket);
		fflush(stdout);
		printf("%d %d %d\n",msg.type, msg.client_id, msg.msg_timestamp);
		clk.update(msg.msg_timestamp);
		if(msg.type == request) {
			req = new client_request(msg.client_id, msg.msg_timestamp);
			request_pq.push(req);
			bzero((char *)&response, sizeof(response));
			response.type = reply;
			response.client_id = my_id;
			response.ref_timestamp = msg.msg_timestamp;
			response.msg_timestamp = clk.get_incremented_time();
			write(*socket, &response, sizeof(response));
		}else if(msg.type == reply) {
			if(pending_map.increment_and_check(msg.ref_timestamp) && (req = (client_request *)request_pq.pop_if_top(msg.ref_timestamp))) {
				pen_req = pending_map.remove(msg.ref_timestamp);
				ser_msg = get_server_msg(pen_req);
				delete pen_req;
				delete req;
				server_queue.push(ser_msg);
								
			}
		} else if(msg.type == release) {
		}
	}
}


server_message *get_server_msg(pending_request *pen_req) {
	server_message * ser_msg = new server_message;
	ser_msg->type = pen_req->type;
	ser_msg->sndr = pen_req->sndr;
	ser_msg->rcvr = pen_req->rcvr;
	ser_msg->amount = pen_req->amount;
	return ser_msg;
}