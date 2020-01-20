#ifndef REQUEST_H
#define REQUEST_H

typedef unsigned int Clientid;
enum message_type{transfer, balance};


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



#endif
