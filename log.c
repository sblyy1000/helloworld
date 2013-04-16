#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>
#include "config.h"
#define LOGFILE "/var/log/server.log"
extern int log_to;
void mylog(char *fmt,...){
	//FILE *fn;
	va_list var;
	pthread_mutex_lock(&(dlog->log_lock));
		va_start(var,fmt);
		if(!dlog->log){
			printf("log fd is null\n");
		}
		vfprintf(dlog->log,fmt,var);
		va_end(var);	
		//fclose(log->log);
	pthread_mutex_unlock(&(dlog->log_lock));
}
log_t* init_log(struct server_conf *srv){
	FILE *fn;
	char *logdir;
	log_t *log;
	if(!srv){
		perror("server conf null");
	}
	if((srv)->logdir){
		logdir=(srv)->logdir;
		//printf("log file is %s\n",logdir);
	}
	else{
		logdir=LOGFILE;
		//printf("log file is %s\n",logdir);
	}
	log=(log_t *)malloc(sizeof(log_t));
	printf("init log start\n");
	if(!log){
		perror("init log error!");
		exit(-1);
	}
	perror("init log ok");
	//log->log_lock=PTHREAD_MUTEX_INITALIZER;
	if(pthread_mutex_init(&(log->log_lock),NULL)<0){
		perror("init log lock error");
		exit(-1);
	}
	perror("init log lock ok");
	#ifdef LOG_DEBUG
		log_to=LOG_2_STDERR;
	#endif
	if(log_to==LOG_2_STDERR)
		log->log=stderr;
	else{
		fn=fopen(logdir,"a");
		//printf("fd is %d\n",fd);
		if(fn<0){
			perror("open log file error\n");
			exit(0);
		}
		log->log=fn;
	}
	return log;

}
void fini_log(log_t *log){
	if(log){
		if(log->log){
			close(log->log);
		}
		if(pthread_mutex_destroy(&(log->log_lock))<0)
			perror("log lock destroy failed");
		}
		free(log);
		log=NULL;
		printf("free log...\n");
}
#ifdef LOG_DEBUG
int main(){
	error_log("this is a test");
	warn_log("this is a test");
	info_log("this is a test");
	debug_log("this is a test");
}
#endif
