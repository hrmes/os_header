#ifndef __MERCKU_CORE_UTILS_IO_H__
#define __MERCKU_CORE_UTILS_IO_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <core/mercku_error.h>

// MError *write_file(const char *path, const char *content);
MError *write_file_lines(const char *path, const char **lines, int lineCnt);
const char *get_file_name(const char *path);
MError *read_int_from_file(const char *path, int *value);
MError *write_int_to_file(const char *path, int value);
MError *write_file_str(const char *path, const char *content);
/**
 * @brief read file content to @content, and set @size to the length of content.
 * @param path
 * @param content the content of file, need to be freed by caller with tracable_free.
 * @param size the length of content.
*/
MError *read_file(const char *path, char **content, uint32_t *size);
MError *read_file_lines(const char *path, char ***lines, uint32_t *line_cnt);
MError *read_file_str(const char *path, char *buf, uint32_t buf_len);
MError *write_file_strf(const char *path, const char *fmt, ...);
MError *read_file_i32(const char *path, int32_t *value);
MError *write_file_i32(const char *path, int32_t value);
MError *read_file_i64(const char *path, int64_t *value);
MError *write_file_i64(const char *path, int64_t value);
MError *read_file_u32(const char *path, uint32_t *value);
MError *write_file_u32(const char *path, uint32_t value);
MError *read_file_u64(const char *path, uint64_t *value);
MError *write_file_u64(const char *path, uint64_t value);
MError *read_file_bool(const char *path, bool *value);
MError *write_file_bool(const char *path, bool value);

/**
 * @brief check if file exists.
*/
bool check_file_exist(const char *path);

/**
 * @brief join strings with @sep.
 *
 * @param dest
 * @param sep
 * @param pieces... will skip NULL and empty string.
 */
void strjoin(char *dest, const char *sep, const char *pieces, ...);
void str_array_join(char *dst, const char *sep, const char **pieces, int pieceCnt);
uint32_t quick_get_file_len(const char *path);
MError *zero_copy_file(const char *src, const char *dst);
MError *zero_copy_file_ext(const char *src, const char *dst, uint32_t offset, uint32_t length);


#endif // __MERCKU_CORE_UTILS_IO_H__