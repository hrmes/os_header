#ifndef __VENDOR_MESH_H__
#define __VENDOR_MESH_H__

#include <stdint.h>
#include <stdbool.h>
#include <utils/mac.h>

#include <core/mercku_constants.h>
#include <core/mercku_error.h>
#include <core/nocapi.h>

#define MERCKU_MAX_NODES 7

typedef enum
{
    SATWireless2G = 0,
    SATWireless5G,
    SATWired,
} StaAccessType;
typedef struct
{
    char local_mac[MERCKU_MAC_LEN];
    char remote_mac[MERCKU_MAC_LEN];
    int rssi;
    MeshBackhaulType bh_type;
} MeshNeighbor;

typedef struct
{
    double cpu;
    uint64_t mem_total;
    uint64_t mem_used;
} SystemResource;

/// @brief mesh 节点上的 sta。
typedef struct
{
    MacHr mac;
    StaAccessType access_type;
    int rssi;
} MeshNodeSta;

typedef struct {
    uint32_t negotiation_rate_Mbps;
    bool linked;
} MeshNodePort;

typedef struct _MeshNode
{
    char version[20];           // firmware version
    char name[MERCKU_NAME_LEN]; // alias
    char ip[MERCKU_IP_LEN + 1]; // lan ip
    char sn[MERCKU_SN_LEN + 1];
    struct
    {
        char wlan_5g[MERCKU_MAC_LEN + 1];
        char wlan_2g[MERCKU_MAC_LEN + 1];
        char wan[MERCKU_MAC_LEN + 1];
        char lan[MERCKU_MAC_LEN + 1];
        char mesh_2g_ap[MERCKU_MAC_LEN + 1];
        char mesh_5g_ap[MERCKU_MAC_LEN + 1];
        char mesh_2g_sta[MERCKU_MAC_LEN + 1];
        char mesh_5g_sta[MERCKU_MAC_LEN + 1];
    } macs;
    MeshNeighbor neighbors[MERCKU_MAX_NODES];
    int neighbors_cnt;
    bool is_gw;
    bool is_master;
    MeshNodeState state;
    SystemResource system_info;
    uint32_t rpc_port;
    MeshNodeSta stations[50];
    uint32_t sta_cnt;
    uint64_t uptime_sec;
    /// @brief 端口信息
    MeshNodePort ports[6];
    uint32_t port_cnt;
} MeshNode;

/**
 * @brief 获取 mesh 邻居列表，不包含自己（top 图）.
 *
 * @param neighbors 节点列表，需要调用者释放内存
 * @param cnt
 * @return MError*
 */
// MError *m_get_mesh_neighbor_nodes(MeshNode **neighbors, uint16_t *cnt);
/**
 * @brief 获取当前节点的邻居信息。只是 mac 和 rssi 信息。
 *
 * @param neighbors
 * @param cnt
 * @return MError*
 */
MError *m_load_neighbors(MeshNeighbor **neighbors, uint16_t *cnt);

/// 将 mesh 配置成 master。
MError *m_mesh_config_master();
/// 将 mesh 配置成 slave。
MError *m_mesh_config_slave();

typedef struct
{
    bool present; // 是否有 mesh 信息
    // 这里长度不重要，只是为了方便调用者分配内存
    char bssid[50];
    char password[50];
} MeshInfo;

/**
 * @brief 获取当前组网的信息。
 *
 * @param info
 * @return MError*
 */
MError *m_mesh_get_bssid(MeshInfo *info);

typedef struct
{
    MacHr mac;
    int rssi;
    StaAccessType access_type;
} MeshTopologyNodeSta;

typedef struct
{
    // 必须是 001122334455 的形式，可使用 mercku_core 的 shrink_mac 方法
    MacHrCompacted al_mac;
    bool is_master;
    MeshNeighbor neighbors[7];
    uint32_t neighbor_cnt;
    MeshTopologyNodeSta stations[50];
    uint32_t sta_cnt;
} MeshTopologyNode;

typedef struct
{
    MeshTopologyNode nodes[MERCKU_MAX_NODES];
    uint32_t node_cnt;
} MeshTopology;

/// @brief 获取当前 mesh topology 的快照。
/// @param topology
/// @return
MError *m_get_mesh_topology(MeshTopology *topology);

#endif // __VENDOR_MESH_H__