#ifndef LISTEN_H
#define LISTEN_H
#include "config.h"
//int listen_sock; //listenqueue[maxfds+1] listenqueue[0] is serversock 
int listen_thread(struct server_conf *);
#endif
