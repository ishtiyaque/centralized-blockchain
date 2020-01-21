#ifndef SYNC_QUEUE_H
#define SYNC_QUEUE_H

#include<vector>
#include<queue>
#include <pthread.h>
#include <semaphore.h>

template <class T, class Container = std::deque <T> >
class sync_queue {
	std::queue<T, Container> q;
	pthread_mutex_t lock;
	sem_t sem;
public:
	sync_queue() {
		pthread_mutex_init(&lock, NULL);
		sem_init(&sem, 0, 0);
	}
	
	void push(T elem) {
		pthread_mutex_lock (&lock);
		q.push(elem);
		pthread_mutex_unlock (&lock);
		sem_post(&sem);
	}

	T front() {
		sem_wait(&sem);
		pthread_mutex_lock (&lock);
		T t = q.front();
		pthread_mutex_unlock (&lock);
		return t;
	}
	void pop() {
		sem_wait(&sem);
		pthread_mutex_lock (&lock);
		q.pop();
		pthread_mutex_unlock (&lock);
		return ;
	}
	T remove() { // Remove the first and return
		sem_wait(&sem);
		pthread_mutex_lock (&lock);
		T t = q.front();
		q.pop();
		pthread_mutex_unlock (&lock);
		return t;
	}
		
	~sync_queue() {
		pthread_mutex_destroy(&lock);
		sem_destroy(&sem);
	}
};


#endif