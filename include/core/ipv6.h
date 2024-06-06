#ifndef __MERCKU_CORE_IPV6_H__
#define __MERCKU_CORE_IPV6_H__

#include <stdint.h>
#include <core/gcc.h>

/// @brief ipv6, 2001:0db8:85a3:0000:0000:8a2e:0370:7334
typedef char IPv6Hr[40];

/// @brief 
typedef uint8_t IPv6Bin[16];

bool ipv6_hr_to_bin(IN const IPv6Hr hr, OUT IPv6Bin bin);
bool ipv6_bin_to_hr(IN const IPv6Bin bin, OUT IPv6Hr hr);


#endif // __MERCKU_CORE_IPV6_H__