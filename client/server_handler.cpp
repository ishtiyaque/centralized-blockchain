#include "server_handler.h"

void *handle_server(void *ignore) {
	server_response response;
	int server_sock;
	unsigned int t;
	while(1) {
		server_message* req = server_queue.remove();
		req->timestamp = clk.get_incremented_time();
		server_sock = socket(AF_INET, SOCK_STREAM, 0);
		while (connect(server_sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
			continue;
		printf("Sending query to Server. Current time: %d\n",req->timestamp);
		write(server_sock,req,sizeof(server_message));
		read(server_sock,&response,sizeof(server_response));
		close(server_sock);
		t = clk.update(response.timestamp);
		if(req->type == balance) {
			printf("Balance is $%lf. ",response.amount);
		}else if(req->type == transfer) {
			printf("%s. ",response.amount ? "SUCCESS" : "INCORRECT");
		}
		printf("Current time %d\n",t);
		delete req;
		
		release_me();
			
	}

}