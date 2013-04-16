#ifndef DECODE_H
#define DECODE_H
#include "http.h"
int request_decode(int,char *,http_request_line_t *);
int get_protocol(char *p);
int get_method(char *m);//"GET" to int
#endif
