#include "utils.h"
#include "globals.h"
#include "server_handler.h"

void init(char * filename) {
	FILE *fp;
	char ip[16];
	int i, portno, my_sock;
	double ignore;
	
	struct sockaddr_in addr;
	
	sem_init(&sem_condition, 0, 0);
	srand (time(NULL));

	if(!(fp = fopen(filename, "r"))) {
		printf("config.txt NOT FOUND\n");
		exit(1);
	}
	fscanf(fp,"%s%d%d",ip, &portno, &num_client);
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(portno);
	pthread_create(&server_handler, 0, handle_server, 0);		
	
	client_sockets = new int[num_client - 1];
	for(int i = 1; i < my_id; i++) {
		bzero((char *) &addr, sizeof(addr));
		fscanf(fp,"%s%d%lf",ip, &portno, &ignore);
		addr.sin_family = AF_INET;
    	addr.sin_addr.s_addr = inet_addr(ip);
    	addr.sin_port = htons(portno);		
		client_sockets[i-1] = socket(AF_INET, SOCK_STREAM, 0);		
		while(connect(client_sockets[i-1],(struct sockaddr *) &addr,sizeof(addr)) < 0)
			continue;
		//printf("Connected with port %d\n",portno);

	}
	
	bzero((char *) &addr, sizeof(addr));
	fscanf(fp,"%s%d%lf",ip, &portno, &ignore);
	my_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(portno);
	bind(my_sock, (struct sockaddr *) &addr, sizeof(addr));

	listen(my_sock, 10);

	
	for(i = my_id + 1; i <= num_client; i++) {
		client_sockets[i - 2] = accept(my_sock,0,0);
		//printf("Received connction\n");
	}	
	/*printf("Socket fd:\n");
	for(int i = 0; i < num_client -1 ; i++) {
		printf("%d ",client_sockets[i]);
	}
	printf("\n*********************************\n");
	*/
	//printf("Established connection with all other clients.\n");
	
	//fflush(stdout);
	fclose(fp);
	return;

}	

int broadcast(const client_message *msg) {	
		if(msg->type == release) {
			printf("Sending RELEASE to every other client. Current time : %d\n", msg->msg_timestamp);
			if(request_pq.size() > 0) {
				client_request *temp = request_pq.top();
				printf("Top of Q: <%d %d>\n",temp->timestamp, temp->client_id);
			}
		}else if(msg->type == request) {
			printf("Sending REQUEST<%d, %d> to every other client\n", msg->msg_timestamp, msg->client_id);
		}
		my_sleep();

		for(int i = 0; i < num_client - 1; i++) {
			write(client_sockets[i], msg,sizeof(client_message));
		}
}

void release_me() {
	client_message msg;
	msg.type = release;
	msg.client_id = my_id;
	msg.msg_timestamp = clk.get_incremented_time();
	broadcast(&msg);
}

void my_sleep() {
	sleep(2 + (rand() % SLEEP_TIME));
}