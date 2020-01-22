#ifndef SYNC_MAP_H
#define SYNC_MAP_H

#include <unordered_map>
#include <pthread.h>

extern unsigned int num_client;

class sync_map {
	std::unordered_map<unsigned int, pending_request *> map;
	pthread_mutex_t lock;
public:
	sync_map() {
		pthread_mutex_init(&lock, NULL);
	}
	void put(pending_request *req) {
		pthread_mutex_lock (&lock);
		map[req->timestamp] = req;
		pthread_mutex_unlock (&lock);
    }
	void increment_r(unsigned int t) {
		pthread_mutex_lock (&lock);
		pending_request * req = map[t];
		req->r_count++;
		pthread_mutex_unlock (&lock);

	}
	
	bool increment_and_check(unsigned int t) {
		pthread_mutex_lock (&lock);
		pending_request * req = map[t];
		req->r_count++;
		bool result = ((req->r_count) == num_client);
		pthread_mutex_unlock (&lock);
		return result;

	}
	
	bool all_reply(unsigned int t) {
		pthread_mutex_lock (&lock);
		pending_request * req = map[t];
		bool result = ((req->r_count) == num_client);
		pthread_mutex_unlock (&lock);
		return result;

	}
	
	pending_request * remove(unsigned int t) {
		pthread_mutex_lock (&lock);
		pending_request * req = map[t];
		map.erase(t);
		pthread_mutex_unlock(&lock);
		return req;

	}


	~sync_map() {pthread_mutex_destroy(&lock);}
};


#endif
