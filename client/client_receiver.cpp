#include "client_receiver.h"
#include <stdio.h>

void *handle_client(void *sock) {
	int *socket = (int *)sock;
	client_message msg;
	while(1) {
		bzero((char *) &msg, sizeof(msg));
		read(*socket, &msg, sizeof(msg));
		printf("%d %d %d\n",msg.type, msg.client_id, msg.msg_timestamp);
	}
}