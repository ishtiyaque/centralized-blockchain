#include "utils.h"

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   //cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
}