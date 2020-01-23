#include "condition_handler.h"
#include "globals.h"

void *handle_condition(void *ignore) {
	client_request * cl_req;
	pending_request * pen_req;
	server_message * ser_msg ;
	while(1) {
		sem_wait(&sem_condition);
		printf("condition handler woke up\n");
		cl_req = request_pq.top();
		if((cl_req->client_id == my_id) && (pending_map.all_reply(cl_req->timestamp))) {
			pen_req = pending_map.remove(cl_req->timestamp);
			request_pq.pop();
			ser_msg = get_server_msg(pen_req);
			delete pen_req;
			delete cl_req;
			server_queue.push(ser_msg);
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