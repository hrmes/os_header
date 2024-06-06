#ifndef __MERCKUOS_CORE_UTILS_MD5_H__
#define __MERCKUOS_CORE_UTILS_MD5_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <core/mercku_error.h>

#define MD5_LEN 32
typedef char MD5[MD5_LEN + 1];

// 计算文件前 len 个字节的 md5
MError *compute_md5_with_len(const char *file, size_t len, MD5 md5);
MError *compute_md5(const char *file, MD5 sum);
// 从文件流中计算 md5。len 为0时，表示读取 EOF 为止。
MError *compute_md5_on_stream(FILE *fp, size_t stream_cursor, size_t len, MD5 sum);
MError *compute_md5_for_str(const char *buffer, uint32_t len, MD5 sum);
bool check_md5_quick(const char *file, MD5 md5);

#endif // __MERCKUOS_CORE_UTILS_MD5_H__