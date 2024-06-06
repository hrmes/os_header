#ifndef __MERCKU_CORE_NET_H__
#define __MERCKU_CORE_NET_H__

#include <stdint.h>
#include <stdbool.h>

#include <core/ipv6.h>

/// @brief ipv4, 1.2.3.4
typedef char IPv4[16];
/// @brief ipv4 指针, 与 IPv4 一样，只是为了传递。
typedef char *IPv4Ptr;

typedef IPv4 IP;

uint32_t ipv4_to_uint32(const IPv4 ip);
void ipv4_from_uint32(IPv4 ip, const uint32_t ip_uint32);
uint32_t ipv4_mask_to_bitcnt(const IPv4 mask);
uint32_t bitcnt_to_ipv4_mask(const uint32_t bitcnt);
uint32_t mask_int_to_bitcnt(uint32_t mask);

bool ipv4_is_valid(const IPv4 ip);

#define ipv4_is_same_subnet(mask, left, right) (mask & left) == (mask & right)


/// @brief 使用 6 字节的数组表示 MAC 地址。
typedef uint8_t MacEth[6];
/// @brief 长度为 6 的数组指针，用于传递 MAC 地址。
typedef uint8_t *MacEthPtr;
/// @brief 可读 mac, 使用 12 字符串表示 MAC 地址。如AA1122334455，不包含冒号。所有字符大写。
typedef char MacHrCompacted[14];
/// @brief 可读 mac 指针，与 MacHrCompacted 一样，只是为了传递。
typedef char *MacHrCompactedPtr;
/// @brief 可读 mac, 使用 17 字符串表示 MAC 地址。如AA:11:22:33:44:55，所有字符大写。
typedef char MacHr[18];
/// @brief 可读 mac 指针，与 MacHr 一样，只是为了传递。
typedef char* MacHrPtr;

bool mac_is_valid(const MacEth mac);
bool mac_is_valid_hr_compacted(const MacHrCompacted mac);
bool machr_is_valid(const MacHr mac);
/**
 * 相互转换
*/
bool mac_convert_hr_compacted_to_eth(const MacHrCompacted hr_mac, MacEth eth_mac);
bool mac_convert_hr_to_eth(const MacHr hr_mac, MacEth eth_mac);
bool mac_convert_eth_to_hr_compacted(const MacEth eth_mac, MacHrCompacted hr_mac);
bool mac_convert_eth_to_hr(const MacEth eth_mac, MacHr hr_mac);
bool mac_convert_hr_to_hr_compacted(const MacHr hr_mac, MacHrCompacted hr_compacted_mac);
bool mac_convert_hr_compacted_to_hr(const MacHrCompacted hr_compacted_mac, MacHr hr_mac);



#endif // __MERCKU_CORE_NET_H__