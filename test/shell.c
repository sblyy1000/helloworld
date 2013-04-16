#include "../unix_sock.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*gcc -o shell shell.c ../unix_sock.o ../log.o  -I ../ */
int main(int argc,char **argv){
	int sock;
	char buf[1024];
		if((sock=connect_process(config_with_ctl))<0){
			perror("connect error");
			exit(-1);
		}
		if(write(sock,argv[1],sizeof(argv[1]))<=0){
			perror("write error");
			close(sock);
			exit(-1);
		}
		close(sock);
		printf("send cmd ok!\n");
}
