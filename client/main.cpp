#include "utils.h"
#include "request.h"

#include "sync_priority_queue.h"
#include "sync_queue.h"

priority_queue <client_request*, vector<client_request*>, client_request_comp> req_q; 
pthread_t server_handler;

pthread_mutex_t mut_server;

pthread_mutex_t mut_time;

unsigned int my_id;
unsigned int my_time; 

int main(int argc, char *argv[]) {
	FILE *fp;
	
	
	
	if(argc < 2) {
		printf("Missing Client id. Exiting...\n");
		exit(1);
	}
	my_id = atoi(argv[1]);
	my_time = 0;
	if(!(fp = fopen("../config.txt", "r"))) {
		printf("config.txt NOT FOUND\n");
		exit(1);
	}
	
	sync_priority_queue <client_request*, vector<client_request*>, client_request_comp> q;
	client_request r(1,20);
	q.push(&r);
	printf("%d\n",q.top()->client_id);
	//fscanf(fp,"%s%d%d",server_ip, &portno, &num_client);
	

	
	return 0;
}
