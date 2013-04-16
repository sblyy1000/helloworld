#ifndef _LOG_H
#define _LOG_H
#include <stdarg.h>
#include <pthread.h>
#include <stdio.h>
#include "config.h"
extern int log_to;//
#define LOG_2_FILE 0
#define LOG_2_STDERR 1
typedef struct {
	pthread_mutex_t log_lock;
	FILE *log;
}log_t;
log_t *dlog;
//extern struct server_conf srv;
void mylog(char *fmt,...);
log_t* init_log(struct server_conf *);
void fini_log(log_t *);
#define error_log(arg) \
mylog("%s %s %5s (%s:%d) %s:%s\n",__DATE__,__TIME__,"err",__FILE__,__LINE__,__FUNCTION__,arg)
#define warn_log(arg) \
mylog("%s %s %5s (%s:%d) %s:%s\n",__DATE__,__TIME__,"warn",__FILE__,__LINE__,__FUNCTION__,arg)
#define info_log(arg) \
mylog("%s %s %5s (%s:%d) %s:%s\n",__DATE__,__TIME__,"info",__FILE__,__LINE__,__FUNCTION__,arg)
#define debug_log(arg) \
mylog("%s %s %5s (%s:%d) %s:%s\n",__DATE__,__TIME__,"debug",__FILE__,__LINE__,__FUNCTION__,arg)
#endif
