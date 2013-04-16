#ifndef NETWORK_H
#define NETWORK_H
#define MAX_CON 4096
#include <pthread.h>
#include <stdlib.h>
#if 0
typedef struct connection_s{
	uint32_t epfd;
	uint32_t client_fd;
	uint32_t c_or_s;
	uint32_t clientip;
	uint32_t serverip
	uint16_t clientport;
	uint16_t serverport;
	//uint32_t timeout;
	//uint32_t unset;
}connection_t;
#endif
/*between worker and listener*/
struct con_stack {
	pthread_mutex_t stack_lock;
	int top;
	int con[MAX_CON];
};
//extern struct con_stack *connections;
int stack_init(struct con_stack *S);
int stack_fini(struct con_stack *S);
int con_pop(struct con_stack *S);
int con_push(struct con_stack *S,int fd);
#endif
