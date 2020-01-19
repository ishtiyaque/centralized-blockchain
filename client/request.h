#ifndef REQUEST_H
#define REQUEST_H

class request{
public:
	uint client_id;
	uint timestamp;
	uint r_count;
	request(Clientid cid, uint ts){client_id = cid; timestamp = ts; r_count = 0;};
};

struct request_comp {
	bool operator()(request *r1, request *r2) {
		if(r1->timestamp == r2->timestamp) {
			return r1->client_id > r2->client_id;
		}
		return r1->timestamp > r2->timestamp;
	}
};

#endif
