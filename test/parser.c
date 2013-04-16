#include "decode.h"
#include "http.h"
#include "http_str.h"
/*
 gcc parser.c ../decode.c ../log.c -I ../
 */
static void print_str_t(char *start,int len){
        char tmp[len+1];
        if(start){
                strncpy(tmp,start,len);
                tmp[len]='\0';
                printf("%s\n",tmp);
        }
}
int main(){
        char buf[1024];
        char *request="GET 1.1.1.1:8080/test2.html HTTP/1.1\r\nCookie:a=a\r\n";
        http_request_line_t request_line;
        request_decode(request,&request_line);
        //printf("request:%s\n",request_line->request_start);
        str_t request_d,method,uri,host,port;
        request_d.data=request_line.request_start;
        request_d.len=request_line.request_end-request_line.request_start+1;
        strncpy(buf,request_d.data,request_d.len);

        //printf("decode request:%d %s\n",STR_T_PRINT(&request_d));
        printf("buf:%s\n",buf);
        puts("uri:");
        print_str_t(request_line.uri_start,request_line.uri_end-request_line.uri_start+1);
        puts("host:");
        print_str_t(request_line.host_start,request_line.host_end-request_line.host_start+1);
        puts("port:");
        print_str_t(request_line.port_start,request_line.port_end-request_line.port_start+1);
}
