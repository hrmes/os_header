#ifndef __MERCKUOS_MESH_H__
#define __MERCKUOS_MESH_H__
#include <stdint.h>
#include <stdbool.h>

#include <core/mercku_error.h>

#define MAC_LEN 14 // 12 + 2, aabbccddeeff
#define IP_LEN 15  //
#define SN_LEN 15
#define MAX_NODES 5

typedef enum
{
    MBError = -1,
    MBWifi2G,
    MBWifi5G,
    MBEth,
} MeshType;

typedef struct
{
    char mac[MAC_LEN];
    int rssi;
    MeshType bh_type;
} MNeighbor;

typedef enum
{
    NSNormal = 0,
    NSUpgrading,
    NSUpgradeFailed,
    NSFwDownloading,
    NSFwDownloadFailed,
    NSFwInstalling,
    NSFwInstallFailed,
    NSRebooting,
    NSResetting,
    NSOffline,
    NSNum
} MNodeState;

typedef struct _MNode
{
    char version[20];   // firmware version
    char name[MAC_LEN]; // alias
    char ip[IP_LEN];    // lan ip
    char sn[SN_LEN];
    MNeighbor neighbors[MAX_NODES];
    int neighbors_cnt;
    bool is_master;
    MNodeState state;
} MNode;

MError *mesh_get_nodes(MNode **nodes, uint32_t *nodes_cnt);

#endif // __MERCKUOS_MESH_H__