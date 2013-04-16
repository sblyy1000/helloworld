#include "network.h"
#include "log.h"
#include <stdlib.h>
#include <pthread.h>
int stack_init(struct con_stack *S){
	int ret;
	//S=(struct con_stack*)malloc(sizeof(struct con_stack));
	//if()
	ret=pthread_mutex_init(&(S->stack_lock),NULL);
	if(ret<0){
		perror("mutex init error");
		return 0;
	}
	S->top=-1;
	printf("set top %d\n",S->top);
	memset(S->con,MAX_CON,0);
	return 1;
}
int stack_fini(struct con_stack *S){
	pthread_mutex_destroy(&S->stack_lock);
	free(S);
	S=NULL;
	return 1;
}
int con_pop(struct con_stack *S){
	int ret;
	if(S->top>-1){
		pthread_mutex_lock(&(S->stack_lock));
		ret=S->con[S->top--];
		debug_log("pop a socket");
		pthread_mutex_unlock(&(S->stack_lock));
		return ret;
	}
	return -1;
}
int con_push(struct con_stack *S,int fd){
	char logstr[1024];
	if(S->top<MAX_CON){
		pthread_mutex_lock(&(S->stack_lock));
		S->con[++S->top]=fd;
		debug_log("push a socket");
		sprintf(logstr,"current connection top is %d",S->top);
		pthread_mutex_unlock(&(S->stack_lock));
		return 1;
	}
	return -1;
}
