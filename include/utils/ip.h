#ifndef __MERCKU_CORE_UTILS_IP_H__
#define __MERCKU_CORE_UTILS_IP_H__

#include <stdint.h>

uint32_t ipv4_to_int(const char *ip);
void int_to_ipv4(uint32_t ip, char *buf);
void netmask_compute(uint8_t netmask, char *buf);

#endif // __MERCKU_CORE_UTILS_IP_H__