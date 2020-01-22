#ifndef SYNC_PRIORITY_QUEUE
#define SYNC_PRIORITY_QUEUE

#include<vector>
#include<queue>
#include <pthread.h>
#include "request.h"
extern unsigned int my_id;

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class sync_priority_queue {
	std::priority_queue<T, Container, Compare> q;
	pthread_mutex_t lock;
public:
	sync_priority_queue() {pthread_mutex_init(&lock, NULL);}	
	void push(T elem) {
		pthread_mutex_lock (&lock);
		q.push(elem);
		pthread_mutex_unlock (&lock);
	}

	T top() {
		pthread_mutex_lock (&lock);
		T t = q.top();
		pthread_mutex_unlock (&lock);
		return t;
	}
	void pop() {
		pthread_mutex_lock (&lock);
		q.pop();
		pthread_mutex_unlock (&lock);
		return ;
	}

	void * pop_if_top(unsigned int ts) {
		pthread_mutex_lock (&lock);
		client_request* req = (client_request*) q.top();
		if((req->client_id == my_id) && (req->timestamp == ts)) {
			q.pop();
		} else {
			req = NULL;
		}
		pthread_mutex_unlock (&lock);
		return (void *) req;
	}

	~sync_priority_queue() {pthread_mutex_destroy(&lock);}
};
#endif
