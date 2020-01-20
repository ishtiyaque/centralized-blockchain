#include "server_handler.h"

void *handle_server(void *ignore) {
	double response;
	int server_sock;
	while(1) {
		server_message* req = server_queue.dequeue();
		server_sock = socket(AF_INET, SOCK_STREAM, 0);
		while (connect(server_sock,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
			continue;
		write(server_sock,req,sizeof(server_message));
		read(server_sock,&response,sizeof(double));
		close(server_sock);
		if(req->type == balance) {
			printf("Balance is $%lf\n",response);
		}else if(req->type == transfer) {
			printf("%s\n",response ? "SUCCESS" : "INCORRECT");
		}
		
		delete req;
			
	}

}