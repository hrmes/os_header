#ifndef __MERCKUOS_CORE_DEBUG_H__
#define __MERCKUOS_CORE_DEBUG_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <constants/mercku_common.h>
#include <core/env_variable.h>

#define print_line(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)

typedef enum
{
    LL_FATAL = LOG_CRIT,
    LL_ERROR,
    LL_WARN,
    LL_NOTICE,
    LL_INFO,
    LL_DEBUG,
} LogLevel;

static void get_current_time(char *curtime, size_t len)
{
    time_t rawTime;
    struct tm *timeInfo;

    // 获取当前时间（协调世界时）
    time(&rawTime);
    timeInfo = gmtime(&rawTime);

    // 格式化时间为字符串
    strftime(curtime, len, "%Y-%m-%d %H:%M:%S", timeInfo);
}

#define LOG_STREAM stderr

extern bool g_log_enabled;

#define pure_printf(fmt, ...)                             \
    do                                                    \
    {                                                     \
        if (is_syslog_disabled())                         \
        {                                                 \
            fprintf(LOG_STREAM, fmt "\n", ##__VA_ARGS__); \
        }                                                 \
        else                                              \
        {                                                 \
            syslog(LOG_INFO, fmt "\n", ##__VA_ARGS__);    \
        }                                                 \
    } while (false)

/// 初始化日志，id 取 NULL，表示使用程序名称。
#define init_log(id)                          \
    do                                        \
    {                                         \
        if (!g_log_enabled)                   \
        {                                     \
            openlog(id, LOG_PID, LOG_DAEMON); \
            g_log_enabled = true;             \
        }                                     \
    } while (false)
#define close_log() closelog()

#define filter_log(level, levelStr, fmt, ...)                                     \
    do                                                                            \
    {                                                                             \
        init_log(NULL);                                                           \
        if ((level) <= LOG_LEVEL)                                                 \
        {                                                                         \
            if (is_syslog_disabled())                                             \
            {                                                                     \
                char curtime[32];                                                 \
                get_current_time(curtime, sizeof(curtime));                       \
                fprintf(LOG_STREAM, "%s[%s] %s:%d: " fmt "\n", curtime, levelStr, \
                        __FILE__, __LINE__, ##__VA_ARGS__);                       \
            }                                                                     \
            else                                                                  \
            {                                                                     \
                syslog(level, "%s:%d: " fmt, __FILE__, __LINE__, ##__VA_ARGS__);  \
            }                                                                     \
        }                                                                         \
    } while (0)

#define debug(fmt, ...) filter_log(LL_DEBUG, "DEBUG", fmt, ##__VA_ARGS__)
#define info(fmt, ...) filter_log(LL_INFO, "INFO", fmt, ##__VA_ARGS__)
#define warning(fmt, ...) filter_log(LL_WARN, "WARN", fmt, ##__VA_ARGS__)
#define xerror(fmt, ...) filter_log(LL_ERROR, "ERROR", fmt, ##__VA_ARGS__)

/// fatal will exit the program.
// 参考 https://voidint.github.io/post/posix/exit-_exit-_exit-atexit/
#define fatal(fmt, ...)                                    \
    do                                                     \
    {                                                      \
        filter_log(LL_FATAL, "FATAL", fmt, ##__VA_ARGS__); \
        _exit(1);                                          \
    } while (0)
#define todo() fatal("TODO, MUST be implemented first.")
#define todof(fmt, ...) fatal("TODO: " fmt, ##__VA_ARGS__)
#define need_todo() xerror("TODO, NEED be implemented first.")
#define need_todo_fmt(fmt, ...) xerror("TODO, NEED be implemented first." fmt, ##__VA_ARGS__)
#define line() debug("line")
#define unreachable() fatal("unreachable code.")
#define expr_str(expr) debug(#expr "=%s", expr)
#define expr_bool(expr) debug(#expr "=%s", (expr) ? "true" : "false")
// 需要强转，不然可能因为入参导致栈内存踩踏。
#define expr_i32(expr) debug(#expr "=%d", (int32_t)expr)
#define expr_u32(expr) debug(#expr "=%u", (uint32_t)expr)
#define expr_u32_hex(expr) debug(#expr "=%x", (uint32_t)expr)
#define expr_u64(expr) debug(#expr "=%llu", (uint64_t)expr)
#define expr_u64_hex(expr) debug(#expr "=%llx", (uint64_t)expr)
#define expr_f32(expr) debug(#expr "=%f", (float32_t)expr)
#define expr_f64(expr) debug(#expr "=%lf", (float64_t)expr)

#define assert_fmt(cond, fmt, ...)                                 \
    do                                                             \
    {                                                              \
        if (!(cond))                                               \
        {                                                          \
            fatal("assert(%s) failed," fmt, #cond, ##__VA_ARGS__); \
        }                                                          \
    } while (0)

#define assert(cond)                           \
    do                                         \
    {                                          \
        if (!(cond))                           \
        {                                      \
            fatal("assert(%s) failed", #cond); \
        }                                      \
    } while (0)


#endif //__MERCKUOS_CORE_DEBUG_H__
