#ifndef __MERCKU_TOOLS_LINUX_NET_H__
#define __MERCKU_TOOLS_LINUX_NET_H__

#include <stdbool.h>
#include <core/all.h>
#include <utils/all.h>

bool ip_is_alive(const IPv4 ip, const char *bridge);

#endif // __MERCKU_TOOLS_LINUX_NET_H__