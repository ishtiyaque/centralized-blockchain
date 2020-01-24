#include "client_receiver.h"
#include<stdio.h>
#include<stdlib.h>

void *handle_client(void *sock) {
	int *socket = (int *)sock;
	int n;
	//printf("Thread created with value %d\n",*socket);
	client_message msg;
	client_request *req;
	client_message response;
	server_message* ser_msg;
	pending_request * pen_req;
	client_request *temp;
	unsigned int t;
	while(1) {
		bzero((char *) &msg, sizeof(msg));
		n = read(*socket, &msg, sizeof(msg));
		if(n < 0) {
			printf("read error. Exiting....\n");
			exit(1);
		}
		//printf("Read from socket %d\n",*socket);
		//fflush(stdout);
		t = clk.update(msg.msg_timestamp);
		if(msg.type == request) {
			printf("Received REQUEST<%d, %d> . Current time: %d\n", msg.msg_timestamp, msg.client_id, t);
			req = new client_request(msg.client_id, msg.msg_timestamp);
			request_pq.push(req);
			temp = request_pq.top();
			printf("Top of Q: <%d %d>\n",temp->timestamp, temp->client_id);

			bzero((char *)&response, sizeof(response));
			response.type = reply;
			response.client_id = my_id;
			response.ref_timestamp = msg.msg_timestamp;
			response.msg_timestamp = clk.get_incremented_time();
			printf("Sending REPLY to Client %d. Current time: %d\n", msg.client_id, response.msg_timestamp);
			my_sleep();
			write(*socket, &response, sizeof(response));
		}else if(msg.type == reply) {
			pending_map.increment_r(msg.ref_timestamp);
			printf("Received REPLY from client %d. Current time: %d\n",msg.client_id, t);
			sem_post(&sem_condition);
		}else if(msg.type == release) {
			request_pq.pop();
			
			printf("Received RELEASE from client %d. Current time: %d\n",msg.client_id, t);
			if(request_pq.size() > 0) {
				temp = request_pq.top();
				printf("Top of Q: <%d %d>\n",temp->timestamp, temp->client_id);
			}
			sem_post(&sem_condition);
		}
	}
}