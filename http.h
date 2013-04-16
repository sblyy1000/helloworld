/**
 * @file
 * @brief HTTP 相关宏，结构及函数定义
 *
 * 
 */
#ifndef HTTP_H
#define HTTP_H

#include "http_str.h"

#define SP     (char)' '                       //!< US-ASCII SP, space (32)
#define CR     (char)'\r'                      //!< US-ASCII CR, carriage return (13)
#define LF     (char)'\n'                      //!< US-ASCII LF, linefeed (10)
#define CRLF   "\r\n"                          //!< HTTP 分隔符

#define HTTP_VERSION_09            0x00000009  //!< HTTP/0.9
#define HTTP_VERSION_10            0x00010000  //!< HTTP/1.0
#define HTTP_VERSION_11            0x00010001  //!< HTTP/1.1
#define HTTP_VERSION_BIT_9             (1<<0)  //!< HTTP/0.9
#define HTTP_VERSION_BIT_10            (1<<1)  //!< HTTP/1.0
#define HTTP_VERSION_BIT_11            (1<<2)  //!< HTTP/1.1

#define HTTP_UNKNOWN                   0       //!< 未知方法
#define HTTP_GET                       (1<<1)  //!< GET, RFC 2616: HTTP/1.1
#define HTTP_HEAD                      (1<<2)  //!< HEAD, RFC 2616: HTTP/1.1
#define HTTP_POST                      (1<<3)  //!< POST, RFC 2616: HTTP/1.1
#define HTTP_PUT                       (1<<4)  //!< PUT, RFC 2616: HTTP/1.1
#define HTTP_DELETE                    (1<<5)  //!< DELETE, RFC 2616: HTTP/1.1
#define HTTP_MKCOL                     (1<<6)  //!< MKCOL, RFC 2518: WebDAV
#define HTTP_COPY                      (1<<7)  //!< COPY, RFC 2518: WebDAV
#define HTTP_MOVE                      (1<<8)  //!< MOVE, RFC 2518: WebDAV
#define HTTP_OPTIONS                   (1<<9)  //!< OPTIONS, RFC 2616: HTTP/1.1
#define HTTP_PROPFIND                  (1<<10) //!< PROPFIND, RFC 2518: WebDAV
#define HTTP_PROPPATCH                 (1<<11) //!< PROPPATCH, RFC 2518: WebDAV
#define HTTP_LOCK                      (1<<12) //!< LOCK, RFC 2518: WebDAV
#define HTTP_UNLOCK                    (1<<13) //!< UNLOCK, RFC 2518: WebDAV
#define HTTP_TRACE                     (1<<14) //!< TRACE, RFC 2616: HTTP/1.1
#define HTTP_SEARCH                    (1<<15) //!< SEARCH, http://msdn.microsoft.com/en-us/library/aa143053%28EXCHG.65%29.aspx
#define HTTP_CONNECT                   (1<<16) //!< CONNECT, RFC 2616: HTTP/1.1
#define HTTP_PATCH                     (1<<17) //!< PATCH, http://tools.ietf.org/html/draft-dusseault-http-patch-16
#define HTTP_VERSION_CONTROL           (1<<18) //!< VERSION-CONTROL, RFC 3253: WebDAV Versioning
#define HTTP_CHECKOUT                  (1<<19) //!< CHECKOUT, RFC 3253: WebDAV Versioning
#define HTTP_UNCHECKOUT                (1<<20) //!< UNCHECKOUT, RFC 3253: WebDAV Versioning
#define HTTP_CHECKIN                   (1<<21) //!< CHECKIN, RFC 3253: WebDAV Versioning
#define HTTP_UPDATE                    (1<<22) //!< UPDATE, RFC 3253: WebDAV Versioning
#define HTTP_LABEL                     (1<<23) //!< LABEL, RFC 3253: WebDAV Versioning
#define HTTP_REPORT                    (1<<24) //!< REPORT, RFC 3253: WebDAV Versioning
#define HTTP_MKWORKSPACE               (1<<25) //!< MKWORKSPACE, RFC 3253: WebDAV Versioning
#define HTTP_MKACTIVITY                (1<<26) //!< MKACTIVITY, RFC 3253: WebDAV Versioning
#define HTTP_BASELINE_CONTROL          (1<<27) //!< BASELINE-CONTROL, RFC 3253: WebDAV Versioning
#define HTTP_MERGE                     (1<<28) //!< MERGE, RFC 3253: WebDAV Versioning

#define HTTP_CONNECTION_UNKNOWN        0       //!< Connection 未设置
#define HTTP_CONNECTION_CLOSE          1       //!< Connection: close
#define HTTP_CONNECTION_KEEP_ALIVE     2       //!< Connection: Keep-Alive

#define HTTP_POST_TYPE_UNKNOWN         0       //!< Content-Type 未设置
#define HTTP_POST_TYPE_URLENCODED      1       //!< Content-Type: application/x-www-form-urlencoded
#define HTTP_POST_TYPE_MULTIPART       2       //!< Content-Type: multipart/form-data, RFC1867

#define HTTP_CONTINUE                      100     //!< Continue, RFC 2616
#define HTTP_SWITCHING_PROTOCOLS           101     //!< RFC 2616
#define HTTP_PROCESSING                    102     //!< Processing, RFC 2518

#define HTTP_OK                            200     //!< RFC2616
#define HTTP_CREATED                       201     //!< RFC2616
#define HTTP_ACCEPTED                      202     //!< RFC2616
#define HTTP_NON_AUTHORITATIVE             203     //!< RFC2616
#define HTTP_NO_CONTENT                    204     //!< RFC2616
#define HTTP_RESET_CONTENT                 205     //!< RFC2616
#define HTTP_PARTIAL_CONTENT               206     //!< RFC2616
#define HTTP_MULTI_STATUS                  207     //!< RFC2518

#define HTTP_MULTIPLE_CHOICES              300     //!< RFC2616
#define HTTP_MOVED_PERMANENTLY             301     //!< RFC2616
#define HTTP_MOVED_TEMPORARILY             302     //!< RFC2616
#define HTTP_SEE_OTHER                     303     //!< RFC2616
#define HTTP_NOT_MODIFIED                  304     //!< RFC2616
#define HTTP_USE_PROXY                     305     //!< RFC2616
#define HTTP_TEMPORARY_REDIRECT            307     //!< RFC2616

#define HTTP_BAD_REQUEST                   400     //!< 请求行不合法, RFC2616
#define HTTP_UNAUTHORIZED                  401     //!< 需要认证, RFC2616
#define HTTP_PAYMENT_REQUIRED              402     //!< RFC2616
#define HTTP_FORBIDDEN                     403     //!< 禁止访问, RFC2616
#define HTTP_NOT_FOUND                     404     //!< 请求的资源不存在, RFC2616
#define HTTP_METHOD_NOT_ALLOWED            405     //!< 不允许的 HTTP 方法, RFC2616
#define HTTP_NOT_ACCEPTABLE                406     //!< RFC2616
#define HTTP_PROXY_AUTHENTICATION_REQUIRED 407     //!< RFC2616
#define HTTP_REQUEST_TIME_OUT              408     //!< RFC2616
#define HTTP_CONFLICT                      409     //!< RFC2616
#define HTTP_GONE                          410     //!< RFC2616
#define HTTP_LENGTH_REQUIRED               411     //!< HTTP 请求需要合法的 Content-Length 字段, RFC2616
#define HTTP_PRECONDITION_FAILED           412     //!< RFC2616
#define HTTP_REQUEST_ENTITY_TOO_LARGE      413     //!< HTTP 请求数据太大, RFC2616
#define HTTP_REQUEST_URI_TOO_LARGE         414     //!< 请求的 URL 太长, RFC2616
#define HTTP_UNSUPPORTED_MEDIA_TYPE        415     //!< 不支持的媒体类型, RFC2616
#define HTTP_RANGE_NOT_SATISFIABLE         416     //!< 请求的范围不满足, RFC2616
#define HTTP_EXPECTATION_FAILED            417     //!< Except 不满足, RFC2616
#define HTTP_UNPROCESSABLE_ENTITY          422     //!< RFC2518
#define HTTP_LOCKED                        423     //!< RFC2518
#define HTTP_FAILED_DEPENDENCY             424     //!< RFC2518
#define HTTP_UPGRADE_REQUIRED              426     //!< RFC2817, Upgrading to TLS Within HTTP/1.1
#define HTTP_RETRY_WITH                    449     //!< MS extension.
#define HTTP_WINDOWS_PARENTAL_CONTROL      450     //!< MS extension.
#define HTTP_REQUEST_BAD_METHOD            479     //!< 不合法的 HTTP 请求方法
#define HTTP_REQUEST_BAD_URI               480     //!< 不合法的 HTTP 请求 URI
#define HTTP_REQUEST_BAD_SCHEMA            481     //!< 不合法的协议 Schema
#define HTTP_REQUEST_BAD_HOST              482     //!< 不合法的请求主机名
#define HTTP_REQUEST_BAD_PORT              483     //!< 不合法的请求端口
#define HTTP_REQUEST_BAD_PROTOCOL          484     //!< 不合法的请求协议
#define HTTP_REQUEST_BAD_PROTOCOL_VERSION  485     //!< 不合法的请求协议版本
#define HTTP_REQUEST_BAD_CRLF              486     //!< 不合法的请求，结尾不是 CR|LF
#define HTTP_REQUEST_BAD_09_METHOD         487     //!< HTTP/0.9 仅支持 GET 方法
#define HTTP_REQUEST_HEADER_BAD_CRLF       488     //!< 不合法的头部域，结尾不是 CR|LF
#define HTTP_RESPONSE_STATUS_TOO_LARGE     489     //!<
#define HTTP_REQUEST_WITHOUT_HOST          490     //!< HTTP 请求没有 Host 字段
#define HTTP_PROTOCOL_VERSION_FORBIDDEN    491     //!< 禁止的 HTTP 协议版本
#define HTTP_USER_AGENT_TOO_LARGE          492     //!< User-Agent 字段内容太长
#define HTTP_COOKIE_TOO_LARGE              493     //!< Cookie 字段内容太长
#define HTTP_REFERER_TOO_LARGE             494     //!< Referer 字段内容太长
#define HTTP_ACCEPT_TOO_LARGE              495     //!< Accept 字段内容太长
#define HTTP_ACCEPT_CHARSET_TOO_LARGE      496     //!< Accept-Charset 字段内容太长
#define HTTP_CONTENT_LENGTH_TOO_LARGE      497     //!< Content-Length 指定的长度太长
#define HTTP_HEADER_CONTENT_TOO_LARGE      498     //!< 头部域内容太长
#define HTTP_HEADER_COUNT_TOO_LARGE        499     //!< 头部域的个数太多

#define HTTP_INTERNAL_SERVER_ERROR         500     //!< 服务器内部错误, RFC2616
#define HTTP_NOT_IMPLEMENTED               501     //!< 不支持的 HTTP 方法, RFC2616
#define HTTP_BAD_GATEWAY                   502     //!< RFC2616
#define HTTP_SERVICE_UNAVAILABLE           503     //!< RFC2616
#define HTTP_GATEWAY_TIME_OUT              504     //!< RFC2616
#define HTTP_VERSION_NOT_SUPPORTED         505     //!< 不支持的 HTTP 版本, RFC2616
#define HTTP_VARIANT_ALSO_VARIES           506     //!< RFC2295, Transparent Content Negotiation in HTTP
#define HTTP_INSUFFICIENT_STORAGE          507     //!< RFC2518
#define HTTP_NOT_EXTENDED                  510     //!< RFC2774, An HTTP Extension Framework
#define HTTP_RESPONSE_ENTITY_TOO_LARGE     599     //!< HTTP 响应数据太大

//py-add-beg-define http check MACRO-1/8/2012
#define HTTP_URI_ARG_NUM_TOO_LARGE	       611     //!<URI中的参数个数太大
#define HTTP_HEAD_NAME_TOO_LARGE           612     //!<头部域中头部名字过长
#define HTTP_COOKIE_NUM_TOO_LARGE          613     //!<cookie个数太大
#define HTTP_POST_ARG_NUM_TOO_LARGE        614     //!<POST参数个数太大
//py-add-end-define http check MACRO-1/8/2012

typedef struct {
    uint32_t            fd;                                 //accept fd
    uint32_t                method;                        //!< HTTP 请求方法

    str_t                   http_protocol;                 //!< HTTP 协议

    char                   *uri_start;                     //!< URI 起始地址
    char                   *uri_end;                       //!< URI 结束地址，包括参数
    char                   *uri_ext;                       //!< URI 文件扩展名起始地址
    char                   *args_start;                    //!< URI 参数起始地址
    char                   *request_start;                 //!< HTTP 请求行的起始地址
    char                   *request_end;                   //!< HTTP 请求行的结束地址
    char                   *method_end;                    //!< HTTP 方法的结束地址
    char                   *schema_start;                  //!< HTTP 请求协议起始地址
    char                   *schema_end;                    //!< HTTP 请求协议结束地址
    char                   *host_start;                    //!< HTTP 请求主机起始地址
    char                   *host_end;                      //!< HTTP 请求主机结束地址
    char                   *port_start;                    //!< HTTP 请求端口起始地址
    char                   *port_end;                      //!< HTTP 请求端口结束地址

    size_t                  complex_uri:1;                 //!< URI with "/." and on Win32 with "//"
    size_t                  quoted_uri:1;                  //!< URI with "%"
    size_t                  plus_in_uri:1;                 //!< URI with "+"
    size_t                  zero_in_uri:1;                 //!< URI with "\0" or "%00"
    size_t                  httpverbit:4;                  //!< HTTP 版本，0.9, 1.0, 1.1
} http_request_line_t;                                     //!< HTTP 请求行结构

#endif // HTTP_SESSION_H_
