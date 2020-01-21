#ifndef REQUEST_H
#define REQUEST_H

typedef unsigned int Clientid;
enum message_type{transfer, balance, request, reply, release};


class client_request{
public:
	Clientid client_id;
	unsigned int timestamp;
	unsigned int r_count;
	client_request(Clientid cid, unsigned int ts);
};

struct client_request_comp {
	bool operator()(client_request *r1, client_request *r2);
};

struct client_message {
	message_type type;
	Clientid client_id;
	unsigned int msg_timestamp;
	unsigned int ref_timestamp;
};

struct server_message {
	message_type type;
	Clientid sndr;
	Clientid rcvr;
	double amount;
};

struct pending_request {
	message_type type;
	Clientid sndr;
	Clientid rcvr;
	double amount;
	unsigned int timestamp;
	unsigned int r_count;
	pending_request(message_type t, Clientid r, double a);
};


#endif
