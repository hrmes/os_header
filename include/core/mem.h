/**
 * @file mem.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2024
 *
 * 支持追踪内存分配和释放。注意：只用于 C 语言部分代码。
 *
 */

#ifndef __MERCKU_CORE_MEM_H__
#define __MERCKU_CORE_MEM_H__

#include <compile/config.h>
#include <stdbool.h>

#include <stdlib.h>

#ifdef TRACE_C_MEM
#define VALID_MEM_FREE_CHECK 1

void *trace_malloc(size_t size, const char *file, int line);
void *trace_calloc(size_t n, size_t size, const char *file, int line);
void trace_free(void *ptr, const char *file, int line);
/**
 * @brief 输出当前还存活的内存。
 *
 */
void dump_live_memory(const char *file);

#define tracable_malloc(size) trace_malloc(size, __FILE__, __LINE__)
#define tracable_calloc(n, size) trace_calloc(n, size, __FILE__, __LINE__)
#define tracable_free(ptr)                       \
    do                                           \
    {                                            \
        if (ptr)                                 \
            trace_free(ptr, __FILE__, __LINE__); \
        ptr = NULL;                              \
    } while (false)

#define raw_calloc(n, size) calloc(n, size)
#define raw_malloc(size) malloc(size)
#define raw_free(ptr)  \
    do                 \
    {                  \
        if (ptr)       \
            free(ptr); \
        ptr = NULL;    \
    } while (false)

// deprecated
#define unsafe_calloc(n, size) calloc(n, size)
// deprecated
#define unsafe_malloc(size) malloc(size)
// deprecated
#define unsafe_free(ptr)  \
    do                 \
    {                  \
        if (ptr)       \
            free(ptr); \
        ptr = NULL;    \
    } while (false)

#define unsafe_calloc(n, size) calloc(n, size)
#define unsafe_malloc(size) malloc(size)
#define unsafe_free(ptr) \
    do                    \
    {                     \
        if (ptr)          \
            free(ptr);    \
        ptr = NULL;       \
    } while (false)

#else // TRACE_C_MEM

#define tracable_calloc(n, size) calloc(n, size)
#define tracable_malloc(size) malloc(size)
#define tracable_free(ptr) \
    do                     \
    {                      \
        if (ptr)           \
            free(ptr);     \
        ptr = NULL;        \
    } while (false)

#define unsafe_calloc(n, size) calloc(n, size)
#define unsafe_malloc(size) malloc(size)
#define unsafe_free(ptr)  \
    do                 \
    {                  \
        if (ptr)       \
            free(ptr); \
        ptr = NULL;    \
    } while (false)

#endif // TRACE_C_MEM
/**
 * @brief 打开信号处理器，用于显示内存。
 *
 */
void turn_on_signal_handler_to_show_memory();

#endif // __MERCKU_CORE_MEM_H__