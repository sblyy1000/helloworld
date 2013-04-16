#ifndef wATCH_H
#define WATCH_H
#include "unix_sock.h"
/*be watched process :receive syn and send ok*/
#define be_watched(path) \
    recv_process(path,send_ok,NULL)

//def int watch_and_exit()		//for config
//def int watch_and_kill()  //for worker
#endif
