#ifndef __MERCKU_CORE_UTILS_MAC_H__
#define __MERCKU_CORE_UTILS_MAC_H__
#include <stdbool.h>

typedef union
{
    char pieces[6][2];
    char raw[16]; // 001122334455
} StructuredMac;

// 00:00:00:00:00:00
bool parse_mac(StructuredMac *mac, const char *str);
// 001122334455
bool parse_shrinked_mac(StructuredMac *mac, const char *str);
// 123456(第个字节代表一部分)
bool parse_mac_from_eth(StructuredMac *mac, const char *eth);
// 00:00:00:00:00:00
const char *mac_to_str(const StructuredMac *mac);
// 001122334455
const char *mac_to_shrinked_str(const StructuredMac *mac);
/**
 * @brief 压缩 MAC 地址。
 *
 * @param src 11:22:33:44:55:66
 * @param dst 112233445566
 */
void shrink_mac(const char *src, char *dst);
/**
 * @brief 扩展 MAC 地址。
 *
 * @param shrink_mac 112233445566
 * @param dst 11:22:33:44:55:66
 */
void expand_mac(const char *shrink_mac, char *dst);

#endif // __MERCKU_CORE_UTILS_MAC_H__