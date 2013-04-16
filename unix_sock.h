#ifndef UNIX_SOCK_H
#define UNIX_SOCK_H
//who recv ,who bind: recv_with_send
#define main_with_config "/tmp/sock_config_with_main"
#define config_with_ctl "/tmp/sock_config_with_ctl"
#define config_with_watch "/tmp/sock_config_with_watch"
#define worker_with_watch "/tmp/sock_worker_with_watch"

typedef void (*callback)(void *);


int recv_process(char *,callback f,void *);
int connect_process(char *);
inline void send_ok(int); 
/*watch process send syn,when not receive ok,do something(f)*/
void watch_process(char *path,callback f,void *);
#endif
