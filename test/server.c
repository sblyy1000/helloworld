#include "unix_sock.h"
#include <stdlib.h>
#include <stdio.h>
static void send_ok(int fd){
	if(write(fd,"ok",sizeof("ok"))){
		printf("send ok\n");
	}
}
int main(){
	recv_process(config_with_ctl,send_ok,NULL);
}
