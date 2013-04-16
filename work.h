#ifndef WORK_H
#define WORK_H
#include "config.h"
#include <sys/epoll.h>
void work_thread(struct server_conf *);
int process_events(int ,struct epoll_event *,struct server_conf*);
//void work_loop(struct server_conf *);
//void shutdown(struct server_conf *,struct connection);
void shut_down(void);
void work_clean(void);

#endif
