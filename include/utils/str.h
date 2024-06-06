#ifndef __MERCKU_CORE_UTILS_STR_H__
#define __MERCKU_CORE_UTILS_STR_H__

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define safe_strlen(str) ((str) ? strlen(str) : 0)
#define str_equals(left, right) (left && right && strcmp(left, right) == 0)
#define prefix_equals(left, right, n) (left && right && strncmp(left, right, n) == 0)
#define str_nequals(left, right, n) (left && right && strncmp(left, right, n) == 0)
#define str_equals_ignore_case(left, right) (left && right && strcasecmp(left, right) == 0)
#define str_nequals_ignore_case(left, right, n) (left && right && strncasecmp(left, right, n) == 0)
#define prefix_equals_ignore_case(left, right, n) (left && right && strncasecmp(left, right, n) == 0)
#define str_has_prefix(str, prefix) (str && prefix && strncmp(str, prefix, strlen(prefix)) == 0)
/**
 * @brief 拼接字符串。注意，这个函数与系统的 strcat 一样，返回的是 dest 的指针。调用者要保证 dest 有足够的空间。
*/
char *strcatf(char *dest, const char *format, ...);

char **str_split(const char *str, const char *delim, size_t *numtokens);
/// 去除尾部的空白字符，如换行、空格等
void str_rtrim(char *str);
/**
 * @brief 去除尾部的指定个数的字符。
*/
void str_rtrim_n_char(char *str, uint32_t n);
/// @brief 获取字符串的尾部。
/// @param src 原字符串
/// @param len 长度。如果该长度超出字符串长度，返回 src.
/// @return 返回尾部字符串的指针。注意，它与 src 共用生命周期，不可以释放。
const char *str_tail(const char *src, uint32_t len);

char **str_split_null_terminated(const char *str, const char *delim);

void free_dimensional_char_array(char **array, int count);
/**
 * @brief 释放一个 null 结尾的字符串数组。
 *
 * @param array
 */
void free_dimensional_char_array_null_terminated(char **array);
char **dimensional_char_array_copy_to_null_terminated(const char **array, size_t arraySize);
/**
 * @brief 复制一个 null 结尾的字符串数组。
 *
 * @param nullTerminatedArray
 * @return char** 返回的数组需要使用 free_dimensional_char_array_null_terminated 释放。
 */
char **dimensional_null_terminated_char_array_dup(const char **nullTerminatedArray);
// NOTE: 此函数返回的是栈空间，所以应该尽快使用
const char *itoa(int i);

/**
 * @brief 拷贝字符串，并将拷贝后的字符串转换为小写。
*/
char *strncpy_lwr(char *dest, const char *src, size_t n);

/**
 * @brief 拷贝字符串，并将拷贝后的字符串转换为大写。
*/
char *strncpy_upr(char *dest, const char *src, size_t n);

char *tracable_dup(const char *src);
char *tracable_dup_n(const char *src, uint32_t n);

#endif // __MERCKU_CORE_UTILS_STR_H__