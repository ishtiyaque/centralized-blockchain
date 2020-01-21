#include "request.h"
#include "globals.h"


client_request::client_request(Clientid cid, unsigned int ts){
	client_id = cid; 
	timestamp = ts; 
	r_count = 0;
}

bool client_request_comp::operator()(client_request *r1, client_request *r2) {
	if(r1->timestamp == r2->timestamp) {
		return r1->client_id > r2->client_id;
	}
	return r1->timestamp > r2->timestamp;
}

pending_request::pending_request(message_type t, Clientid r, double a) {
	type = t;
	sndr = my_id;
	rcvr = r;
	amount = a;
	timestamp = clk.get_incremented_time();
	r_count = 0;
}