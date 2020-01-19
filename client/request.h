#ifndef REQUEST_H
#define REQUEST_H

class request{
public:
	uint client_id;
	uint timestamp;
	uint r_count;
	request(Clientid cid, uint ts){client_id = cid; timestamp = ts; r_count = 0;};
}

#endif