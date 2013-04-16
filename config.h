#ifndef _CONFIG_H
#define _CONFIG_H

#define _USE_CONF
#define configfile "./server.xml"
#include "log.h"
typedef struct{
	char *key;
	char *value;
	struct config *next;
}config;
struct server_conf{
	char *ip;
	short port;
	char *docroot;
	char *logdir;
	int maxfds;
}srv;
void init_conf(struct server_conf *);
void destory_conf(struct server_conf *);
char *read_conf(char *key);
void recv_cmd_loop();
#endif
