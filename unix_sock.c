#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include "log.h"
#include "unix_sock.h"
#include <stdlib.h>
int recv_process(char *path,callback f,void *parm){
	struct sockaddr_un ser_addr;
        int sock,newsock;
	char buf[1024];
        if((sock=socket(AF_UNIX,SOCK_STREAM,0))<0){
                error_log("create UNIX SOCK error");
                exit(-1);
        }
        ser_addr.sun_family=AF_UNIX;
        strcpy(ser_addr.sun_path,path);
        unlink(path);
        if(bind(sock,(struct sockaddr*)&ser_addr,(sizeof(ser_addr.sun_family)+strlen(ser_addr.sun_path)))<0){
                error_log("bind UNIX SOCK error");
                exit(-1);
        }
        if(listen(sock,5)<0){
                error_log("listen UNIX SOCK error");
                exit(-1);
        }

        while(1){

                if((newsock=accept(sock,NULL,NULL))<0){
                        warn_log("accept unix sock error");
			continue;
                }

        	if(read(newsock,buf,sizeof(buf)))
        	/*parm 1:watch,operate with newsock,parm 0:do_cmd,operate with buf*/
		    if(parm)
		    	f(newsock);
		else f(buf);
        }
        close(sock);
        return 0;
}
int connect_process(char *path){
	int sock;
        struct sockaddr_un cli_addr;

        if((sock=socket(AF_UNIX,SOCK_STREAM,0))<0){
                error_log("unix sock client create socket error");
                return -1;
        }
        cli_addr.sun_family=AF_UNIX;
        strcpy(cli_addr.sun_path,path);//unsafe
        if(connect(sock,(struct sockaddr*)&cli_addr,(sizeof(cli_addr.sun_family)+strlen(cli_addr.sun_path)))<0){
                 error_log("unix sock client connect to error");
                 return -1;
        }
	return sock;
}
void send_ok(int fd){
    if(write(fd,"ok",sizeof("ok"))){
    	//printf("send ok\n");
	}
}
void watch_process(char *path,callback f,void *p){
	int sock;
	char buf[1024];
	while(1){
		if((sock=connect_process(path))<0)
		    break;
		if(write(sock,"hello",sizeof("hello"))<=0)
		    break;
		if(read(sock,buf,sizeof(buf))<=0)
		    break;
		//if buf==ok
		sleep(3);
	}
	close(sock);
f(p);
}
