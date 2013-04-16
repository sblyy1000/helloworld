#ifndef _RESPONSE_H
#define _RESPONSE_H
#include "http.h"
#include "http_str.h"
#include "config.h"
#include <stdlib.h>
/*
response : char *
1.add response line (protocol,status_code,status_desc)
2.add headers (response,char *header)
3.add body      (response,char *content)
other function: http_response_realloc(response_t,size_t size)
free_response(response_t)
http_response_send_error(int fd,int statuccode,char *status_desc,int content_length,char *error_content)
 */
typedef str_t http_response_t;

#define free(p) do {\
	printf("%s:%d:%s:free(0x%lx)\n", __FILE__, __LINE__,__func__,(unsigned long)p);\
	free(p);\
	}while(0)
#if 0
#define malloc(p) malloc(p);\
	printf("%s:%d:%s:malloc(%d)\n", __FILE__, __LINE__,__func__,(unsigned long)p)
#endif
int http_response_realloc_for_buf(http_response_t *,char *);
int http_response_send_error(int,int,char *,char *);
int http_response_create(struct server_conf *,http_request_line_t *,http_response_t *);
int http_response_add_status_line(http_response_t *,int,char *);
int http_response_add_headers(http_response_t *,char *);
int http_response_add_body(http_response_t *,char *);
int free_response(http_response_t *);
#endif
