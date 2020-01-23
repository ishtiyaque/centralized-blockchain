#ifndef SYNC_MAP_H
#define SYNC_MAP_H

#include <unordered_map>
#include <pthread.h>

#include "request.h"

extern unsigned int num_client;

class sync_map {
	std::unordered_map<unsigned int, pending_request *> map;
	pthread_mutex_t lock;
public:
	sync_map();
	void put(pending_request *req);
	void increment_r(unsigned int t);
	bool increment_and_check(unsigned int t);
	bool all_reply(unsigned int t);
	pending_request * remove(unsigned int t);
	~sync_map();
};


#endif
