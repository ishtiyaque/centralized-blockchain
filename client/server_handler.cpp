#include "server_handler.h"

void *handle_server(void *ignore) {
	server_response response;
	int server_sock;
	while(1) {
		server_message* req = server_queue.remove();
		req->timestamp = clk.get_incremented_time();
		server_sock = socket(AF_INET, SOCK_STREAM, 0);
		while (connect(server_sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
			continue;
		printf("Server connected at socket %d\n",server_sock);
		write(server_sock,req,sizeof(server_message));
		read(server_sock,&response,sizeof(server_response));
		close(server_sock);
		clk.update(response.timestamp);
		if(req->type == balance) {
			printf("Balance is $%lf\n",response.amount);
		}else if(req->type == transfer) {
			printf("%s\n",response.amount ? "SUCCESS" : "INCORRECT");
		}
		
		delete req;
		
		release_me();
		//sem_post(&sem_condition);
			
	}

}