#include "clock.h"

my_clock::my_clock() {
	time=0;
	pthread_mutex_init(&lock, NULL);
}
unsigned int my_clock::get_incremented_time() {
	unsigned int t;
	pthread_mutex_lock (&lock);
	t = ++time;
	pthread_mutex_unlock (&lock);
	return t;
}
void my_clock::update(unsigned int t) { //incremented receive time
	pthread_mutex_lock (&lock);
	time = t > (time + 1) ? t : (time + 1);
	pthread_mutex_unlock (&lock);
	return;
}
	
my_clock::~my_clock() {
	pthread_mutex_destroy(&lock);
}