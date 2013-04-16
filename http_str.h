/**
 * @file
 * @brief 字符串处理函数
 *
 * 
 */
#ifndef HTTP_STR_H
#define HTTP_STR_H

#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <fnmatch.h>
#include <sys/types.h>


/**
 * @brief 字符串结构
 */
typedef struct {
    size_t   len;  //!< 字符串长度
    char    *data; //!< 起始地址
} str_t;

#define STR_T_PRINT(s) (int)((s)->len), (s)->data         //!< 字符串结构 (str_t) 输出参数

#define xtolower(c) (((c) >= 'A' && (c) <= 'Z') ? ((c) | 0x20) : (c))  //!< 返回 c 的小写字符，如果可以
#define xtoupper(c) (((c) >= 'a' && (c) <= 'z') ? ((c) & ~0x20) : (c)) //!< 返回 c 的大写字符，如果可以

#define http_string(str)     { sizeof(str) - 1, str }             //!< 常量字符串初始化
#define http_null_string     { 0, NULL }                          //!< 空字符串

#endif