#include "utils.h"
#include "blockchain.h"

int main() {
	unsigned int my_time = 0;
	int i;
	int server_sock, client_sock, portno, num_client;
	double amount;
	char buffer[255], server_ip[16];
	sockaddr_in addr;
	FILE *fp;
	Blockchain blk_chn;
	server_message from_client;
	server_response to_client;

	if(!(fp = fopen("../config.txt", "r"))) {
		printf("config.txt NOT FOUND\n");
		exit(1);
	}
	fscanf(fp,"%s%d%d",server_ip, &portno, &num_client);

	for(i = 1; i <= num_client; i++) {
		fscanf(fp,"%s%d%lf",buffer,(int *)buffer, &amount );
		blk_chn.make_transaction(0, i, amount);
	}
	fclose(fp);


	//blk_chn.print();
	if((server_sock = socket(AF_INET, PROTOCOL, 0)) < 0){
		printf("Error opening server socket. Exiting...\n");
		exit(1);
	}
	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(server_ip);
    addr.sin_port = htons(portno);

	if((bind(server_sock, (struct sockaddr *) &addr, sizeof(addr))) < 0) {
		printf("Error binding server socket. Exiting...\n");
		exit(1);

	}
	printf("Started Server...\n");
	listen(server_sock, 10);
	//printf("%d\n",balance);

	while(1) {
		
		if((client_sock = accept(server_sock,0,0)) < 0) {
			printf("Error accepting client. Exiting...\n");
			exit(1);
		}
		read(client_sock,&from_client,sizeof(server_message));
			
		my_time = MAX(my_time, from_client.timestamp);
		++my_time;
		if(from_client.type == balance) {
			printf("Received Balance query from Client %d. Current time: %d\n",from_client.sndr, my_time);
			amount = blk_chn.get_balance(from_client.sndr);
		}else if(from_client.type == transfer) {
			printf("Received Transfer query amounting $%lf from Client %d to Client %d. Current time: %d\n",from_client.amount, from_client.sndr, from_client.rcvr, my_time);
			amount = blk_chn.make_transaction(from_client.sndr, from_client.rcvr, from_client.amount);
			if(amount) {
				printf("Transaction Successful.\n");
			}else {
				printf("Transaction failed. Insufficient balance.\n");
			}
		}
		to_client.timestamp = ++my_time;
		to_client.amount = amount;
		printf("Sending respose to Client %d. Current time: %d\n", from_client.sndr, my_time);
		sleep(3);
		write(client_sock,&to_client,sizeof(server_response));
		close(client_sock);
	}
	close(server_sock);

	return 0;
}
