#ifndef MY_CLOCK_H
#define MY_CLOCK_H
#include <pthread.h>

class my_clock {
	unsigned int time;
	pthread_mutex_t lock;

public:
	my_clock(); 
	unsigned int get_time();
	void update(unsigned int t); 
	unsigned int get_incremented_time();
	~my_clock();
	
};
#endif