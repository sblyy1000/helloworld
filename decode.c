#include "decode.h"
#include "http.h"
#include "log.h"

static void print_str_t(char *fmt,char *start,int len){
        char tmp[len+1];
        if(start){
                strncpy(tmp,start,len);
                tmp[len]='\0';
                printf(fmt,tmp);
        }
}
int request_decode(int fd,char *request,http_request_line_t *request_line){
	char method[10];
	char *tmp;
	if(!request){
		debug_log("request buf is null");
		return NULL;
	}
	if(!request_line){
		debug_log("request line buf is null");
		return NULL;
	}
        request_line->fd=fd;
	request_line->request_start=request;
	request_line->request_end=strstr(request,"\r\n")-1;
	request_line->method_end=strpbrk(request," \t")-1;
	//print_str_t("method:%s\n",request_line->request_start,request_line->method_end-request_line->request_start+1);
	//HTTP/1.0  :  GET / HTTP/1.0
	//how to decode: GET 1.1.1.1:8080/a.html HTTP/1.1
	//between method_end and uri_start is host:port
	
	request_line->uri_start=strstr(request,"/");//first '/' occer is uri poisition
	request_line->uri_end=strpbrk(request_line->uri_start," \t")-1;
	//print_str_t("uri:%s\n",request_line->uri_start,request_line->uri_end-request_line->uri_start+1);
	request_line->schema_start=strstr(request_line->uri_end,"HTTP");
	//uri_ext=
	request_line->args_start=strchr(request_line->uri_start,'?')+1;
	request_line->schema_end=request_line->request_end;
	
	request_line->http_protocol.data=request_line->schema_start;
	request_line->http_protocol.len=request_line->schema_end-request_line->schema_start+1;
	if((request_line->method_end+sizeof(char)+1)==request_line->uri_start){
		request_line->host_start=NULL;
		request_line->host_end=NULL;
		request_line->port_start=NULL;
		request_line->port_end=NULL;
	}//no host:port
	else{
		request_line->host_start=request_line->method_end+sizeof(char)+1;
		if((tmp=strchr(request_line->host_start,':'))==NULL){
			request_line->host_end=strchr(request_line->host_start,'/')-sizeof(char);
			request_line->port_start=NULL;
			request_line->port_end=NULL;
		}//only have host,no port
		else{
			request_line->host_end=tmp-sizeof(char);
			request_line->port_start=tmp+sizeof(char);
			request_line->port_end=strchr(request_line->port_start,'/')-sizeof(char);;
		}//have host:port
	}//have host
	if((tmp=strstr(request,"/."))||(tmp=strstr(request,"//"))){
		if(tmp<request_line->uri_end)
			request_line->complex_uri=1;
	}
	request_line->complex_uri=0;
	
	request_line->http_protocol.data=request_line->schema_start;
	request_line->http_protocol.len=request_line->schema_end-request_line->schema_start;
        return 1;
}
int get_method(char *m){
	int method;
	if(!strcmp(m,"GET"))
		method=HTTP_GET;
	else if(!strcmp(m,"POST"))
		method=HTTP_POST;
	else
		method=HTTP_UNKNOWN;
	return method;
}

int get_protocol(char *p){
	int protocol;
	if(!strcmp(p,"HTTP/1.1"))
		protocol=HTTP_VERSION_11;
	else if(!strcmp(p,"HTTP/1.0"))
		protocol=HTTP_VERSION_10;
	else
		protocol=HTTP_VERSION_09;
	return protocol;
}
