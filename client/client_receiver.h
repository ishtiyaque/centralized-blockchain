#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "utils.h"
#include "globals.h"


void *handle_client(void *sock) ;
server_message *get_server_msg(pending_request *pen_req);

#endif
