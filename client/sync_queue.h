#ifndef SYNC_QUEUE_H
#define SYNC_QUEUE_H

#include<vector>
#include<queue>
#include <pthread.h>

template <class T, class Container = deque<T> >
class sync_queue {
	std::queue<T, Container> q;
	pthread_mutex_t lock;
public:
	sync_queue() {pthread_mutex_init(&lock, NULL);}	
	void push(T elem) {
		pthread_mutex_lock (&lock);
		q.push(elem);
		pthread_mutex_unlock (&lock);
	}

	T front() {
		pthread_mutex_lock (&lock);
		T t = q.front();
		pthread_mutex_unlock (&lock);
		return t;
	}
	void pop() {
		pthread_mutex_lock (&lock);
		q.pop();
		pthread_mutex_unlock (&lock);
		return ;
	}
};


#endif