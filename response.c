#include "response.h"
#include <assert.h>
#include "log.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#define MAX_FILENAME_LEN 128
#define error_file_max 1024
#define BUFF_SIZE 1024
#define ROOTDIR "/usr/local/myhttpd/www"
#define HTTP_11_STR "HTTP/1.1"
#define HTTP_10_STR "HTTP/1.0"
#define desc_200 "ok"
#define desc_404 "NOT FOUND"
#define content_404 "<html><head><title>not found</title></head><body>this page is not found</body></html>"
#define desc_500 "internal error"
#define content_500 "<html><head><title>error</title></head><body>server error</body></html>"
#define con_close(response) do{http_response_add_headers(response,"Connection: close");}while(0)
static char *http_response_readfile(char *path){
    int fd;
    char *buf=NULL;//must init,realloc need
    char logstr[BUFF_SIZE];
    int n,i=0;
    fd=open(path,O_RDONLY);
    if(fd<0){
		error_log("open request file error!");
		//perror("open failed");
		close(fd);
		return NULL;
    }
    debug_log("open request file ok");
	do{
		//printf("(%s.%d)relloc start\n",__FILE__,__LINE__);
		buf=(char *)realloc(buf,(BUFF_SIZE+(i*BUFF_SIZE))*sizeof(char));
		//printf("(%s.%d)relloc end\n",__FILE__,__LINE__);
		if(!buf){
			debug_log("realloc for buf failed!");
			close(fd);
			return NULL;
		}
		n=read(fd,buf+i*BUFF_SIZE,BUFF_SIZE);
		if(n<BUFF_SIZE){
			debug_log("read file end");
			close(fd);
			//printf("(%s.%d)read end,0x%x",__FILE__,__LINE__,buf);
			return buf;
		}
		i++;
	}while(n=BUFF_SIZE);
	//n<0
	close(fd);
	return NULL;
   
}
static char *http_response_ls(char *server_root){
        DIR *root;
        char *buf;

        struct dirent *dirinfo;
	char logstr[1024];
	sprintf(logstr,"enter response ls dir process,root dir is :%s",server_root);
	debug_log(logstr);
	//printf("server root dir is :%s\n",server_root);
        if(server_root)
		root=opendir(server_root);
        if(!root){
	//perror("open error!");
		sprintf(logstr,"open root dir failed,error: %s",strerror(errno));
            error_log(logstr);
            //closedir(root);
            return NULL;
        }
        else{
		debug_log("open root dir ok");
                buf=(char *)malloc(BUFF_SIZE*sizeof(char));
                if(buf){
                        memset(buf,0,BUFF_SIZE);
                        while(dirinfo=readdir(root)){
                                strcat(buf,dirinfo->d_name);
				strcat(buf,"\n");
                        }
            		closedir(root);
                        return buf;
                }
                else
                    error_log("response ls buffer is NULL!");
            		closedir(root);
                    return NULL;
        }
}
int http_response_realloc_for_buf(http_response_t* response,char *buf){
    int tmp;
    int len=strlen(buf);//这里最好不要用strlen，因为如果是二进制文件，可能造成截断
    if(response->len==0){
    	tmp=(len/BUFF_SIZE+1)*BUFF_SIZE;//1024对齐
    	response->data=(char *)malloc(tmp*sizeof(char));//first time
	}
    if((int)(BUFF_SIZE-(response->len)%BUFF_SIZE-len)<0){
    		//加int是因为可能会转化为无符号整数，导致条件恒假
		//not enough for buf
    		tmp=(((response->len)/BUFF_SIZE+1)*BUFF_SIZE)+(len-BUFF_SIZE+response->len%BUFF_SIZE);//1024对齐,原有长度+需要新分配长度
		response->data=realloc(response->data,tmp*sizeof(char));
	}
    //every time malloc BUFF_SIZE,cmp(len,response->len)
	//printf("response ptr is (%x)\n",response->data);
	//printf("buf len is %d\n",len);
//    response->data=realloc(response->data,response->len+len);
	//printf("pre len is %d\n",response->len);
        memmove(response->data+response->len,buf,len);
        response->len+=len;
	//printf("after len is %d\n",response->len);
        return 1;

}
int http_response_send_error(int fd,int status_code,char *status_line,char *content){
        char buf[error_file_max];
        sprintf(buf,"%s %d %s\r\nContent-length: %d\r\nConnection: close\r\n\r\n%s",HTTP_11_STR,status_code,status_line,strlen(content),content);
        if(write(fd,buf,strlen(buf))<=0)
            return -1;
        return 1;
}
int http_response_create(struct server_conf *server,http_request_line_t *request,http_response_t *response){
        char path[MAX_FILENAME_LEN];
        char buf[BUFF_SIZE];
        char *ls=NULL,*content=NULL;
	int response_len;
        if(server&&server->docroot)
                strncpy(path,server->docroot,strlen(server->docroot)+1);
        else
                strncpy(path,ROOTDIR,strlen(ROOTDIR)+1);
        if(request->uri_start==request->uri_end){
        //if(request->uri_end=request->uri_start){	
                ls=http_response_ls(path);
                if(ls){
			//printf("ls len is %d\n",strlen(ls));
                        http_response_add_status_line(response,200,desc_200);
                        sprintf(buf,"Content-length:%d",strlen(ls));
                        http_response_add_headers(response,buf);
			con_close(response);
                        http_response_add_body(response,ls);
			//printf("response: %d\n%s\n",response->len,response->data);
			//printf("header length is %d\n",strlen(buf)+17);
                        write(request->fd,response->data,response->len);
                        free(ls);
			free_response(response);
			return 1;
                }//endif
		else{
			error_log("open for document root dir failed!");
			http_response_send_error(request->fd,500,desc_500,content_500);
			return(-1);

		}//end else
        }//endif uri is "/",do ls -la
        else{
		/*main work*/	
		printf("path:%s\n",path);
		strncat(path,request->uri_start,request->uri_end-request->uri_start+1);
		printf("path:%s\n",path);
		content=http_response_readfile(path);
		if(!content){
		//404
		    http_response_send_error(request->fd,404,desc_404,content_404);
		    debug_log("send not found!");
		    return 1;
		}
		//printf("content is 0x%x\n",content);
                http_response_add_status_line(response,200,desc_200);
		response_len=strlen(content);
                sprintf(buf,"Content-length:%d",response_len);
                http_response_add_headers(response,buf);
		con_close(response);
                //printf("response:%s\n",content);
		http_response_add_body(response,content);
		//printf("content ok\n");
                write(request->fd,response->data,response->len);
                //printf("content len is %d\n",strlen(content));
		//printf("free content(0x%x)\n",content);
		free(content);
		content=NULL;
		free_response(response);
		return 1;
        }//end else
}
int http_response_add_status_line(http_response_t *response,int status_code,char *status_line){
        char buf[BUFF_SIZE];
        sprintf(buf,"%s %d %s\r\n",HTTP_11_STR,status_code,status_line);
        if(http_response_realloc_for_buf(response,buf)>0){
            debug_log("add response line ok!");
            return 1;
        }
        else{
            error_log("add response line error!");
            return -1;
        }
}
int http_response_add_headers(http_response_t *response,char *header){
    char buf[BUFF_SIZE];
    sprintf(buf,"%s\r\n",header);
    if(http_response_realloc_for_buf(response,buf)>0){
        debug_log("add header ok!");
        return 1;
    }
    error_log("add header failed!");
    return -1;
}
int http_response_add_body(http_response_t *response,char *body){
        char *buf;
        http_response_realloc_for_buf(response,"\r\n");
        if(http_response_realloc_for_buf(response,body)>0){
		//printf("add response body ok!%s,%d\n",__FILE__,__LINE__);
            debug_log("add response body ok");    
            return 1;
        }
        error_log("add response body error!");
        return -1;
}
int free_response(http_response_t *response){
        //printf("(%s.%d)start free response\n",__FILE__,__LINE__);
	//printf("%s\n",response->data);
	free(response->data);
        //printf("(%s.%d)end free response\n",__FILE__,__LINE__);
        response->data=NULL;
	response->len=0;
        debug_log("free response buffer!");
}
