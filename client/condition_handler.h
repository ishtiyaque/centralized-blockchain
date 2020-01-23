#ifndef CONDITION_HANDLER_H
#define CONDITION_HANDLER_H

#include "request.h"
#include<stdio.h>

void *handle_condition(void *ignore);
server_message *get_server_msg(pending_request *pen_req);


#endif