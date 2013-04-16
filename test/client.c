#include "../unix_sock.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main(){
	int sock;
	char buf[1024];
	while(1){
		if((sock=connect_process(config_with_ctl))<0){
			perror("connect error");
			exit(-1);
		}
		if(write(sock,"hello",sizeof("hello"))<=0){
			perror("write error");
			close(sock);
			exit(-1);
		}
		if(read(sock,buf,sizeof(buf))<=0){
			//close(sock);
			//perror("read error");
			//exit(-1);
		}
		close(sock);
		printf("recv message %s\n",buf);
		sleep(3);
	}
}
