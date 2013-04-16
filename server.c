#include "log.h"
#include "server.h"
#include "unix_sock.h"
#include "listen.h"
#include "watch.h"
#include "work.h"
#include "config.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>
#include <sys/select.h>
#include <signal.h>
#define WORK_PROCESS_NUM 1
#define WORK_THREAD_NUM 2
#define MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
extern int errno;
extern int log_to=LOG_2_FILE;
int isdaemon;
static void sigint_handler(int sig){
	fini_log(dlog);
	shut_down();
	//warn_log("shut down!!");
}
static void mydaemon(void) {
	int fd;
	if (0 != fork()) exit(0);//fork使子进程继承父进程的进程组，但是新的pid
	if (-1 == setsid()) exit(0);//设置回话id，使其成为新会话的首进程，进程组组长，失去控制终端
	signal(SIGHUP, SIG_IGN);
	if (0 != fork()) exit(0);//有 则pgid=sid,但是pid不等。  没有这句话，则pid=pgid=sid
	//为了防止进程再次获得控制终端，也可以只fork一次
	//if (0 != chdir("/")) exit(0);
	
	fd=open("/dev/null",O_RDWR);
	dup2(fd,STDIN_FILENO);
	dup2(fd,STDOUT_FILENO);
}
static void usage(void){
	printf("usage:\n \
	-c configfile : set the config file path,default is current dir\n \
	-p : print config\n \
	-l logpath : set the log path,default is /var/log/server.log\n \
	-d : debug mode\n");
}
static void parse_arg(int argc,char **argv){
	char ch;
	if(argc<2){
		usage();
		exit(-1);
	}
	while((ch=getopt(argc,argv,"c:pl:d"))!=-1){
		switch(ch){
			case 'c':
				printf("config file is : %s\n",optarg);
				break;
			case 'p':
				printf("print config\n");
				break;
			case 'l':
				if(!strcmp(optarg,"stderr"))
					log_to=LOG_2_STDERR;
				printf("log path is : %s\n",optarg);
				break;
			case 'd':
				printf("run in debug mode\n");
				isdaemon=0;
				//log_to=LOG_2_STDERR;
				break;
			default:
				printf("no arg\n");
				break;
		}
	}
}
main(int argc,char **argv){
	int tmp;
	char tmp_buf[128];
	int child=0;
	int child_num=WORK_PROCESS_NUM;
	pid_t pid;				//the pid of worker child process
	pthread_t config_tid,watch_tid,work_tid,listen_tid,worker1,worker2;	
	/*start main thread*/
	//extern struct server_conf  srv;
	/*sig init*/
	signal(SIGINT,sigint_handler);
	isdaemon=1;
	parse_arg(argc,argv);
	if(isdaemon)
		mydaemon();
	perror("init server start");
	init_conf(&srv);
	perror("init server ok");
	dlog=init_log(&srv);
	perror("init log ok");
	if(pthread_create(&config_tid,NULL,recv_cmd_loop,NULL)<0){
		error_log("create config thread error");
		//exit(-1);
	}
	debug_log("create config thread sucessful");
	/*main thread*/
	/*parent process:watch*/
	while(isdaemon&&(!child)){
		if(child_num>0){
			switch((pid=fork())){
				case -1:
					return -1;
				case 0:
					child=1;
					break;
				default:
					child_num--;
					tmp=open("/var/run/server.pid",O_RDWR|O_CREAT,MODE);
					sprintf(tmp_buf,"%d",pid);
					write(tmp,tmp_buf,strlen(tmp_buf));
					close(tmp);
					break;
			}
		}
		else{
			wait(NULL);
			child_num++;
		}
	}
	if((!isdaemon)||(child&&isdaemon)){
	//listen_thread(&srv);
	pthread_create(&listen_tid,NULL,listen_thread,&srv);
	pthread_create(&worker1,NULL,work_thread,&srv);
	pthread_create(&worker2,NULL,work_thread,&srv);
	pthread_join(listen_tid,NULL);
	//pthread_join(work_tid,NULL);
	//work_loop(&srv);
	}
}
