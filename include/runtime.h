#ifndef __MERCKU_LINUX_TOOL_RUNTIME_H__
#define __MERCKU_LINUX_TOOL_RUNTIME_H__

#include <stdint.h>
#include <stdlib.h>
#include <core/gcc.h>

#include <core/mercku_error.h>

typedef struct
{
    uint64_t total_bytes;
    uint64_t used_bytes;
} SystemMemInfo;

typedef struct
{
    double cpu;
    SystemMemInfo mem;
} SystemResourceInfo;

MError *load_system_resource_info(SystemResourceInfo *info);
MError *load_cpu_usage(double *cpu_usage_percentage);
MError *load_memory_usage(uint64_t *total_bytes, uint64_t *used_bytes);

typedef struct 
{
    uint32_t speed_Mbps;
    bool linked;
} EthtoolOutput;

MError *run_ethtool(IN const char *iface, OUT EthtoolOutput *output);

MError *bridge_attach_interface(const char *bridge, const char *iface);
MError *bridge_detach_interface(const char *bridge, const char *iface);


#endif // __MERCKU_LINUX_TOOL_RUNTIME_H__