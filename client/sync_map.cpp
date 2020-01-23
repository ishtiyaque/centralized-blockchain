#include "sync_map.h"


sync_map::sync_map() {
	pthread_mutex_init(&lock, NULL);
}
void sync_map::put(pending_request *req) {
	pthread_mutex_lock (&lock);
	map[req->timestamp] = req;
	pthread_mutex_unlock (&lock);
}
void sync_map::increment_r(unsigned int t) {
	pthread_mutex_lock (&lock);
	pending_request * req = map[t];
	req->r_count++;
	pthread_mutex_unlock (&lock);

}

bool sync_map::increment_and_check(unsigned int t) {
	pthread_mutex_lock (&lock);
	if(map.find(t) == map.end()) return false;
	pending_request * req = map[t];
	req->r_count++;
	bool result = ((req->r_count) == (num_client-1));
	pthread_mutex_unlock (&lock);
	return result;
}

bool sync_map::all_reply(unsigned int t) {
	pthread_mutex_lock (&lock);
	if(map.find(t) == map.end()) return false;
	pending_request * req = map[t];
	bool result = ((req->r_count) == (num_client-1));	
	pthread_mutex_unlock (&lock);
	return result;

}

pending_request *sync_map::remove(unsigned int t) {
	pthread_mutex_lock (&lock);
	pending_request * req = map[t];
	map.erase(t);
	pthread_mutex_unlock(&lock);
	return req;

}


sync_map::~sync_map() {pthread_mutex_destroy(&lock);}

