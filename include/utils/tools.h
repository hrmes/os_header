#ifndef __MERCKU_TOOLS_H__
#define __MERCKU_TOOLS_H__

#include <netinet/in.h>

#include <core/mercku_error.h>

/// @brief 执行子进程调用并返回标准输出。
/// @param output_size: output 的大小。内部会减去尾部的 '\0' 一个字符。
MError *popen_with_result(const char *cmd, char *output, uint32_t output_size);
MError *systemf(const char *fmt, ...);

MError *get_ip(const char *iface, struct in_addr *ip);

/// @brief 解析域名。
MError *dns_parse_domain(const char *domain, char *ip);

uint64_t current_time_ms(void);
uint64_t current_time_sec();
double round_double(double x, int decimal);

// 如果 src 存在，则将它 copy 到 dst
#define safely_copy_char_ptr(dst, src) \
    do                                 \
    {                                  \
        char *tmp_src = (src);         \
        if (tmp_src)                   \
            dst = strdup(tmp_src);     \
    } while (false)

// 如果 src 存在，则将它 copy 到dst；
// 如果 dst 存在，则释放它。
#define safely_replace_and_copy_char_ptr(dst, src) \
    do                                             \
    {                                              \
        debug("kk");                               \
        unsafe_free(dst);                          \
        debug("kk");                               \
        char *tmp_src = (src);                     \
        debug("kk");                               \
        if (tmp_src)                               \
            debug("kk");                               \
            dst = strdup(tmp_src);                 \
    } while (false)

#define safely_copy_char_ptr_to_array(dst_array, src_ptr)   \
    do                                                      \
    {                                                       \
        char *tmp_src = (src_ptr);                          \
        if (tmp_src)                                        \
            strncpy(dst_array, tmp_src, sizeof(dst_array) - 1); \
    } while (false)


#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

MError *random_buff(uint8_t *buf, size_t len);

#define stringify(x) #x

#endif // __MERCKU_TOOLS_H__