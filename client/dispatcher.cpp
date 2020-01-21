#include "dispatcher.h"

void *dispatch(void *ignore) {
	client_request *cl_req;
	client_message cl_mes;
	
	while(1) {
		pending_request* req = pending_queue.remove();
		pending_map.put(req);
		cl_req = new client_request(req->sndr, req->timestamp);
		request_pq.push(cl_req);
		bzero((char *)&cl_mes, sizeof(cl_mes));
		cl_mes.type = request;
		cl_mes.client_id = req->sndr;
		cl_mes.msg_timestamp = req->timestamp;
		
		broadcast(&cl_mes);			
	}

}