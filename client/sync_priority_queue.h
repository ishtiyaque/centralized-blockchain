#ifndef SYNC_PRIORITY_QUEUE
#define SYNC_PRIORITY_QUEUE

#include<vector>
#include<queue>
#include <pthread.h>

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
};
#endif