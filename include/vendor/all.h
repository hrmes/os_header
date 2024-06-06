/**
 * @file all.h
 * @author Allen (yalong.zou@mercku.com)
 * @brief
 * @version 0.1
 * @date 2023-12-14
 *
 * @copyright Copyright (c) 2023
 *
 * 说明：
 * 1. 所有不支持的方法，可以使用 core/mercku_error.h 中定义的 EPlatformNotSupport 错误。
 *
 */
#ifndef __MERCKU_VENDOR_ALL_H__
#define __MERCKU_VENDOR_ALL_H__

#include <stdint.h>
#include <stdbool.h>

#include <core/mercku_constants.h>
#include <core/mercku_error.h>
#include <core/mercku_basic.h>
#include <core/nocapi.h>
#include <core/net.h>
#include <utils/mac.h>
#include <core/gcc.h>

#include <core/sn.h>
#include <core/net.h>
#include "mesh.h"
#include "iptables.h"

typedef struct
{
    bool enabled;                          /* 0打开, 1关闭*/
    DdnsService type;                      /* 0: DynDNS, 1: 花生壳 */
    uint8_t domain[MERCKU_DOMAIN_LEN + 1]; /* 域名 */
    uint8_t username[MERCKU_USER_LEN + 1];
    uint8_t password[MERCKU_PASSWORD_LEN + 1];
} DDnsCfg;

/// 获取 DDNS 配置
MError *m_ddns_get_cfg(DDnsCfg *cfg);
MError *m_ddns_set_cfg(const DDnsCfg *cfg);
MError *m_ddns_apply();
typedef enum
{
    PFRPTcp = 0,
    PFRPUdp,
    PFRPTcpUdp,
} PortFWRuleProtocol;
/// port forward
typedef struct
{
    char name[MERCKU_NAME_LEN + 1]; /* 描述 */
    char id[MERCKU_NAME_LEN];       /* 内部用位图实现 */
    bool enabled;                   /* 1:enable, 0:disenble */
    PortFWRuleProtocol protocol;
    char internal_ip[MERCKU_IP_LEN + 1]; /* 内部ip */
    char external_ip[MERCKU_IP_LEN + 1]; /* 外部ip */
    uint32_t internal_start_port;
    uint32_t internal_end_port;
    uint32_t external_start_port;
    uint32_t external_end_port;
} PortFWRule;
/// 端口转发的规则。
/// 兼容旧版本，新 vendor 只需要返回即可。
MError *m_portforward_get_rules(PortFWRule *rules, int *count);

// firewall; vendor 可以不实现。
#define MERCKU_WAN_PING_LIMITED_IP_MAXIMUM 32
typedef struct
{
    bool enabled;
    char mode[20];
    char limited_ips[MERCKU_WAN_PING_LIMITED_IP_MAXIMUM][MERCKU_IP_LEN + 1];
    int ip_cnt;
} FireWallCfg;

MError *m_firewall_wan_get(FireWallCfg *cfg);
MError *m_firewall_get(bool *dos);
MError *m_firewall_set(const bool dos);
MError *m_firewall_wan_set(FireWallCfg *cfg);
MError *m_firewall_apply();

// url filter. vendor 暂时不用实现。
typedef struct
{
    char mac[20];
    uint32_t num; // host num
    char host[MERCKU_HOST_MAX][MERCKU_HOST_LEN + 1];
    bool enabled;
} UrlFilterRule;

// MError *muf_get_all_rules(UrlFilterRule *rules, int *count);
MError *m_urlfilter_get_rule(const char *mac, UrlFilterRule *rule);
MError *m_urlfilter_set_rule(const UrlFilterRule *rule);
MError *m_urlfilter_delete_rule(const char *mac, const char **hosts, int host_count);
MError *m_urlfilter_apply();

typedef enum mercku_work_role_e
{
    WRNotset = 0,
    WRMaster,
    WRSlave,
} WorkRole;

// 兼容旧版本，新 vendor 只需要返回 NULL 即可。
MError *m_work_role_get(WorkRole *role);

/// @brief 路由器的工作模式。
typedef enum mercku_work_mode_e
{
    WMNotset = 0,
    WMGateway = 1,
    WMBridge = 2,
    WMWisp = 3,
    WMRepeater = 4
} WorkMode;
// 获取当前工作模式. 兼容旧代码，新 vendor 可以不实现。
MError *
m_workmode_get(WorkMode *mode);
MError *m_workmode_apply();

/// @brief 重启当前路由器.
void m_reboot();
void m_reset();

/// @brief 检查密码是否正确。
bool m_validate_password(const char *username, const char *encryptedPasswd);

/// @brief 获取当前底层包版本。一般用于升级比较。
const SemVer *m_current_vendor_version();

// /// @brief 获取当前定时开关机配置。
// MError *m_get_schedule_wifi_cfg(ScheduleWifiCfg *cfg);
// /// @brief 设置定时开关机配置。
// MError *m_set_schedule_wifi_cfg(const ScheduleWifiCfg *cfg);

// 使用 iso3166 来获取国家码。
MError *m_tz_get(Timezone *tz);
MError *m_tz_set(const Timezone *tz);
MError *m_tz_apply();

#define DEVICE_MAC_LEN 32

typedef struct
{
    char name[64];
    MacHrCompacted mac;
} BlacklistDevItem;

typedef struct
{
    char name[MERCKU_HOST_LEN + 1];
    IPv4 ip;
    MacHrCompacted mac;
    bool online; // 是否在线
    StaAccessType band;
    uint64_t rtspeedup_bytes_ps;
    uint64_t rtspeeddown_bytes_ps;
    uint64_t onlinetime; // seconds
    uint64_t rx_bytes;
    uint64_t tx_bytes;
    int32_t rssi;
    int32_t guest_id; // guest id. only for guest wifi.
    uint64_t negotiation_rate_bytes_ps;
    uint64_t offline_at_sec; // 这个考虑由上层自己记录
} Sta;

typedef struct
{
    BlacklistDevItem list[MERCKU_BLACKLIST_MAX];
    int count;
} BlacklistCfg;

// 获取黑名单列表。暂时不用实现。
MError *m_blacklist_load(BlacklistCfg *list);
MError *m_blacklist_set(const BlacklistCfg *blacklist);
MError *m_del_blacklist(const char **mac, int count);
MError *m_blacklist_apply();

#define MAX_DEVICE_COUNT 100
typedef struct
{
    Sta list[MAX_DEVICE_COUNT];
    int count;
} StaListVO;

// 获取当前连接的设备列表。最多返回100个。
MError *m_sta_get_list(StaListVO *vo);

/// @brief 获取访客网络上的 sta 列表。
/// @param guest_id
/// @param vo
/// @return
MError *m_get_guest_sta_list(int guest_id, StaListVO *vo);

// speed limit
typedef struct
{
    bool enabled;
    uint32_t upKbps;
    uint32_t downKbps;
    MacHrCompacted mac;
} SpeedLimitCfg;
// 优先级降低
MError *m_speedlimit_get_cfg(const MacHrCompacted mac, SpeedLimitCfg *cfg);
MError *m_speedlimit_set_cfg(const SpeedLimitCfg *cfg);
MError *m_speedlimit_apply();

// wifi
typedef enum mercku_encrypt_e
{
    ETOpen = 0,
    ETWep = 1,
    ETWpa = 2,
    ETWpa2 = 4,
    ETWpa2Mixed = 6,
    ETWapi = 7,
    ETWpa3 = 9,
    ETWpa3Mixed = 10,
} EncryptType;

typedef enum
{
    WBMAp = 0,
    WBMMesh,
    WBMApMesh,
    WBMSta, // STA
    WBMWds,

    WBMUnknown
} WifiBandMode;

typedef enum
{
    WM11ac = 0, // wifi 5
    WM11ax,     // wifi 6
} WifiHwMode;

typedef enum
{
    WBWAuto = 0,
    WBWHt20 = 20,       // 20MHz
    WBWHt40 = 40,       // 40MHz
    WBWHt40Plus,        // 40+MHz自适应
    WBWHt40Minus,       // 40-MHz
    WBWHt80 = 20,       // 80MHz
    WBWHt80Plus80 = 40, // 80+80MHz
    WBWHt160 = 80,      // 160MHz
    WBWNum
} WifiBandWidth;

typedef struct
{
    char ssid[MERCKU_SSID_LEN];
    char password[MERCKU_MAX_PSK_LEN];
    EncryptType encrypt;
    bool enabled;
    bool hidden;
    WifiBandMode mode;
    bool auto_channel;      // 自动信道
    int chan_num;           // 用户手动设置的信道号
    WifiBandWidth chan_wid; // 定义成枚举，或者取值范围。
    WifiHwMode hw_mode;
    uint32_t tx_power; // 发射功率百分比, 0-100
} WifiBandCfg;

// 用于增量修改，即只传递需要修改的部分
typedef struct
{
    const char *ssid;
    const char *password;
    const EncryptType *encrypt;
    const bool *enabled;
    const bool *hidden;
    bool *auto_channel; // 是否开启自动信道，开启时 chan_num 不传或传0
    const WifiBandMode *mode;
    const int *chan_num; // 信道
    const int *chan_wid; // 频宽
    const WifiHwMode *hw_mode;
    const uint32_t *tx_power; // 百分比0~100
} DeltaWifiBandCfg;

typedef struct
{
    uint32_t duration;
    uint32_t expired;
    uint32_t remaining_time;
} GuestWifiTimeStatus;

typedef enum
{
    Unset = 0, // 用于占位
    Sun,
    Mon,
    Tue,
    Wed,
    Thu,
    Fri,
    Sat
} Weekday;

typedef struct
{
    int hour;
    int minute;
} WifiScheduleTime;

MError *m_get_main_2g_cfg(WifiBandCfg *cfg);
MError *m_get_main_5g_cfg(WifiBandCfg *cfg);
MError *m_wifi_delta_configure_main_2g(const DeltaWifiBandCfg *cfg);
MError *m_wifi_delta_configure_main_5g(const DeltaWifiBandCfg *cfg);
MError *m_wifi_configure_main_2g(const WifiBandCfg *cfg);
MError *m_wifi_configure_main_5g(const WifiBandCfg *cfg);
MError *m_wifi_apply();

typedef enum
{
    ScheduleTimeBand2G,
    ScheduleTimeBand5G,
    ScheduleTimeBand25G = 0,

} ScheduleTimeBandsType;
// wifi_schedule
typedef struct WifiSchedule
{
    int32_t id;
    char *time_begin;
    char *time_end;
    char *schedule;
    // int32_t weekint;
    bool enabled;
    char *bands;
    ScheduleTimeBandsType bandstype;
} WifiSchedule;
MError *m_get_wifi_schedule(WifiSchedule **schedule, uint16_t *cnt);
MError *m_update_wifi_schedule(WifiSchedule *schedule);
MError *m_wifi_schedule_apply();

MError *m_get_guest_2g_cfg(WifiBandCfg *cfg);
MError *m_get_guest_5g_cfg(WifiBandCfg *cfg);
/**
 * @brief 暂时不用实现。
 *
 * @param status
 * @return MError*
 */
MError *m_guest_wifi_get_time_status(GuestWifiTimeStatus *status);
MError *m_guest_wifi_set_time_status(const GuestWifiTimeStatus *status);

MError *m_set_guest_2g_cfg(const WifiBandCfg *cfg);
MError *m_set_guest_5g_cfg(const WifiBandCfg *cfg);
MError *m_guest_wifi_apply(bool m_guest_wifi_apply);

SN *m_get_sn();

// clone mac adresses
typedef struct
{
    MacHrCompacted dft;
    MacHrCompacted current;
} WanHwma;

typedef struct
{
    // char  *mac;
    MacHrCompacted mac;
    // char mac[13];
    WanHwma wanhwma;
    uint32_t index;
    Device device;

} MacAdressCfg;

// todo 清理
MError *m_apply_mac_adress();
// 获取 wan 口工作地址和出厂地址。
MError *m_wan_mac_update(MacHrCompacted mac);
// MError *m_wan_mac_update(MacAdressCfg *cfg);

/**
 * @brief 获取 wan 口的默认 mac 地址。dft_mac 表示出厂 mac 地址。
 *
 * @param index wan 口索引。
 * @param mac
 * @return MError*
 */
MError *m_get_wan_dft_mac(uint32_t index, MacHrCompacted mac);
/// @brief 获取 lan 口数量。
uint32_t m_get_lan_count();
/// @brief 获取 lan 口的默认 mac 地址。
MError *m_get_lan_dft_mac(uint32_t index, char *mac);
/// @brief 获取 lan 口的 mac 地址。
MError *m_get_lan_mac(uint32_t index, char *mac);

MError *m_get_mesh_5g_ap_mac(char *mac);
MError *m_get_mesh_2g_ap_mac(char *mac);
MError *m_get_mesh_2g_sta_mac(char *mac);
MError *m_get_mesh_5g_sta_mac(char *mac);

MError *m_get_main_2_4g_mac(char *mac);
MError *m_get_main_5g_mac(char *mac);
MError *m_get_guest_2_4g_mac(char *mac);
MError *m_get_guest_5g_mac(char *mac);

bool m_support_wps_mesh();
bool m_support_wired_mesh();
MError *m_start_wireless_mesh();
MError *m_start_wired_mesh();

typedef enum wan_type_e
{
    WTStatic = 0,
    WTDhcp = 1,
    WTPppoe = 2,
} WanType;
typedef enum dns_mode_e
{
    DMAuto = 0,
    DMManual
} DnsMode;

typedef struct
{
    IP ip;
    IP gateway;
    IP mask;
    IP dns[5];
    uint32_t dns_cnt;
} MNetInfo;

MError *m_is_wan_enabled(bool *enabled);
MError *m_get_wan_type(WanType *type);
EXPORT_API MError *m_get_wan_netinfo(MNetInfo *info);
MError *m_get_lan_netinfo(MNetInfo *info);
MError *m_get_dns_mode(DnsMode *mode);
MError *m_set_dns_mode(const DnsMode mode);
MError *m_set_wan_static(const NetInfo *net);
typedef struct
{
    char username[40];
    char password[40];
} PPPoECfg;

MError *m_get_pppoe_cfg(PPPoECfg *cfg);
MError *m_set_wan_pppoe(const char *account, const char *password);
MError *m_set_wan_dhcp();

/**
 * @brief 重启网络
 *
 * @return MError*
 */
MError *m_reload_network();
// MError *m_wan_update_cfg(const MeshInfoWanNetUpParam *cfg);

typedef struct
{
    int32_t prefix_len;
    IPv6Hr address;
} Ipv6Addr;

typedef struct
{
    bool share_ipv4_credentials; // 是否共享 wan 的用户名和密码
    char username[64];           // 长度没有什么共通之处，所以就不使用常量了。注意使用的时候要用 sizeof，这样就可以避免到处是数字。
    char password[64];
    Ipv6Addr dns[5];
    uint32_t dns_cnt;
} Wan6CfgPppoe;

typedef struct
{
    Ipv6Addr ip;
    Ipv6Addr gateway;
    Ipv6Addr dns[5];
    uint32_t dns_cnt;
} Wan6CfgStatic;

typedef struct
{
    Ipv6Addr dns[5];
    uint32_t dns_cnt;
} Wan6CfgDhcp;

typedef struct
{
    bool disabled;
    Wan6Mode mode;
    Wan6CfgPppoe pppoe;    // mode == W6MPPPoE 时有效
    Wan6CfgDhcp dhcp;      // mode == W6MDHCP 时有效
    Wan6CfgStatic static_; // mode == W6MStatic 时有效
} Wan6Cfg;

typedef struct
{
    Ipv6Addr ip;
    Ipv6Addr gateway;
    Ipv6Addr dns[5];
    uint32_t dns_cnt;
} Wan6NetInfo;

// ipv6
MError *m_wan6_get_netinfo(Wan6NetInfo *cfg);
MError *m_wan6_get_pppoe_netinfo(Wan6NetInfo *cfg);

MError *m_wan6_get_cfg(Wan6Cfg *cfg);
MError *m_wan6_update_cfg(const Wan6Cfg *cfg);
MError *m_apply_wan6_net();

/// @brief 获取 DNS 列表，dns_list 是一个 char* 的列表，空间由 vendor 分配。

typedef struct
{
    char dns[3][64]; // 最多支持3个。
    int count;
} DnsListVO;

// 获取当前配置的 dns 列表
MError *m_get_dns_list_cfg(DnsListVO *vo);
// 设置 dns 列表，会在应用后才生效.
MError *m_set_dns_list_cfg(const DnsListVO *vo);

typedef struct
{
    /**
     * hardware port id, int。 M2:0, M6/M6A:4
     */
    int32_t id;
    char name[40];
    enum VlanPortType typ;
} MVlanPortPort;

typedef struct
{
    MVlanPortPort port;
    bool tagged;
} MVlanPort;

typedef struct
{
    int32_t id;
    bool enabled;
    int32_t priority;
    bool is_bridged;
    char name[40];
    MVlanPort ports[20];
    int port_cnt;
} MVlan;

MError *m_set_vlan(const MVlan *vlans, const int cnt);
MError *m_get_vlan(MVlan *vlans, int *cnt);

typedef enum vlan_type_e
{
    VT_8021Q_UNKNOW = 0,
    VT_8021Q_NAT,
    VT_8021Q_NAT_HW,
    VT_8021Q_BRIDGE,
} VlanType;

#define PORT_NAME_LEN 32

#define ROUTER_PORT_MAX 5

typedef struct vlan_config_t
{
    int enable;
    int vlan_id;
    int priority;
    VlanType type;
    VlanPort ports[ROUTER_PORT_MAX];
    int ports_num;
    unsigned char vlan_name[MERCKU_NAME_LEN + 1];
} VlanRule;

MError *m_get_vlan_cfg(VlanRule **cfg, int count);
MError *m_set_vlan_cfg(const VlanRule *cfg);
MError *m_vlan_apply();

typedef struct pptp_enctype_s
{
    unsigned int mppe;
    unsigned int mppc;
} PptpCfg;

typedef struct openvpn_config_s
{
    unsigned char config[MERCKU_MAX_FILE_PATH_LEN + 1];
} OpenVpnCfg;

typedef enum vpn_protocol_e
{
    VP_L2TP = 0,
    VP_PPTP,
    VP_OPENVPN,
} VPNProtocol;

typedef struct vpn_item
{
    unsigned int id;
    unsigned char name[MERCKU_VPN_NAME_LEN + 1];
    VPNProtocol protocol;
    unsigned char server[MERCKU_VPN_SERVER_LEN + 1];
    unsigned char username[MERCKU_VPN_USERNAME_LEN + 1];
    unsigned char password[MERCKU_VPN_PASSWORD_LEN + 1];
    PptpCfg pptp;
    OpenVpnCfg openvpn;
} VpnCfg;

/// @brief 获取当前 VPN 列表。此接口用于兼容旧数据，vendor 可以不实现。
/// @param list 数组指针，用于存放 VPN 列表。
/// @param count
/// @return
MError *m_vpn_load_rules(VpnCfg **list, int *count);

// 是否支持 openvpn
bool m_vpn_support_openvpn();
bool m_vpn_support_pptp();
bool m_vpn_support_l2tp();
bool m_vpn_support_wireguard();

typedef struct
{
    char config_file[128];
    char username[64];
    char password[64];
} VpnOpenCfg;

MError *m_vpn_openvpn_cfg(const VpnOpenCfg *cfg);
MError *m_vpn_openvpn_clear_cfg();
MError *m_vpn_openvpn_apply();
bool m_vpn_openvpn_is_working();

typedef struct
{
    char public_key[128];
    char preshared_key[128];
    char endpoint_host[64];
    uint32_t endpoint_port;
    char allowed_ips[10][64];
    uint32_t allowed_ips_cnt;
    uint32_t persistent_keepalive_sec;
    bool route_allowed_ips;
} VpnWireguardCfgPeer;

typedef struct
{
    struct
    {
        char private_key[128];
        char addresses[10][64];
        uint32_t address_count;
        uint32_t listen_port;
        uint32_t mtu;
    } interface;
    VpnWireguardCfgPeer peers[3];
    uint32_t peer_cnt;
    const char *iface_name;
} VpnWireguardCfg;
MError *m_vpn_wireguard_clear_cfg();
MError *m_vpn_wireguard_cfg(const VpnWireguardCfg *cfg);
MError *m_vpn_wireguard_apply();
bool m_vpn_wireguard_is_working();

typedef struct
{
    char username[64];
    char password[64];
    char host[100];
} VpnL2tpCfg;
MError *m_vpn_l2tp_cfg(const VpnL2tpCfg *cfg);
MError *m_vpn_l2tp_clear_cfg();
MError *m_vpn_l2tp_apply();
bool m_vpn_l2tp_is_working();

typedef struct
{
    char username[64];
    char password[64];
    char host[100];
    bool mppe;
    bool mppc;
} VpnPptpCfg;
MError *m_vpn_pptp_cfg(const VpnPptpCfg *cfg);
MError *m_vpn_pptp_clear_cfg();
MError *m_vpn_pptp_apply();
bool m_vpn_pptp_is_working();

typedef struct
{
    char configFile[MERCKU_MAX_FILE_PATH_LEN + 1];
    unsigned char username[MERCKU_VPN_USERNAME_LEN + 1];
    unsigned char password[MERCKU_VPN_PASSWORD_LEN + 1];
} OpenVpnSetting;

MError *m_vpn_configure_openvpn(const OpenVpnSetting *cfg);

typedef struct vpn_global
{
    unsigned int default_vpn;
    unsigned int enabled;
} VpnGlobalCfg;

typedef struct vpn_status
{
    bool connected;
    uint64_t connected_time_sec; // if connected == true
    struct
    {
        int error_code;
        char error_msg[MERCKU_VPN_ERROR_MSG_LEN + 1];
    } error; // if connected == false
} VpnStatus;

typedef struct
{
    int country;   // 设置的国家码
    int ipCountry; // ip 所在的国家码
} RegionID;

typedef struct
{
    uint32_t region_id;
    const char *region_iso_name;
} RegionUpdateVO;

/**
 * @brief 获取当前的国家码。采用 ISO 3166 标准。你可以使用 libmercku_core.so 中的 iso3166_get_by_code/iso3166_get_by_alpha2 来获取。
 *
 * @param region_code_iso3166
 * @return MError*
 */
MError *m_get_country(uint32_t *country_code_iso3166);
MError *m_set_country(const uint32_t country_code_iso3166);


typedef enum
{
    LCStart,
    LCRed = LCStart,
    LCGreen,
    LCBlue,
    LCWhite,
    LCCyan,   // Blue + Green
    LCOrange, // Red + Green
    LCOff,
    LCEnd,
} LedColor;

MError *m_configure_led(LedColor color, int blinkHz);
MError *m_apply_led();

typedef struct
{
    bool enabled;
    ScheduleTime begin_time;
    ScheduleTime end_time;
} LedTimeLimitVO;

MError *m_get_led_time_limit(LedTimeLimitVO *cfg);

typedef struct
{
    bool enabled;
    uint16_t weekday_cnt;
    Weekday weekdays[7];  // 以 Unset 结尾
    unsigned char hour;   // 0-23, 0时区
    unsigned char minute; // 0-59
} AutoUpgradeCfg;

// 兼容旧设备。新 vendor 不用实现。
MError *m_auto_upgrade_get_cfg(AutoUpgradeCfg *cfg);

typedef struct
{
    char id[8]; // 一般是一个数字
    bool enabled;
    ScheduleWeekday weekdays[7];
    uint8_t begin_hour;
    uint8_t begin_minute;
    uint8_t end_hour;
    uint8_t end_minute;
} TimeLimitRule;

#define TIME_LIMIT_RULE_MAX 10

typedef struct
{
    MacHrCompacted mac;
    int ruleCnt;
    TimeLimitRule rules[TIME_LIMIT_RULE_MAX];
} DeviceTimeLimitCfg;

#define TIME_LIMIT_DEVICE_MAX 10

typedef struct
{
    bool enabled;
    int deviceCnt;
    DeviceTimeLimitCfg devices[TIME_LIMIT_DEVICE_MAX];
} GlobalTimeLimitCfg;

MError *m_time_limit_get_global_cfg(GlobalTimeLimitCfg *cfg);

MError *m_time_limit_set_rule(const char *mac, const TimeLimitRule *rule);
MError *m_time_limit_del_rule(const char *mac, const char **ids, int count);

MError *m_time_limit_apply();

/// 路由器处于初始化状态
/// 此方法只是为了兼容 m6a/m6 系列，新产品不需要实现。
MError *m_router_been_initialized(bool *initialized);

/**
 * @brief 由于不同的平台对 webui（网页控制端）的支持不一样，为了避免依赖，merckuOS 通过回调方式进行注入，用以接管 web 的请求。
 *
 */

/**
 * @brief 支持 webui。
 *
 * @return true
 * @return false
 */
bool m_support_webui();

/**
 *
 */
typedef MError *(*WebUIRequestHandler)(const char *req, char **resp);
MError *m_register_webui_request(WebUIRequestHandler handler);
/// @brief 启动 webui, 在 m_register_webui_request 调用后，才能调用此函数。一般是使用ubus_loop()来监听ubus的请求。
/// 对于不需要run 的实现，直接返回即可。
void m_webui_run();

// wan 口是否已经连接。
bool m_is_wan_linked();

/// @brief 获取 wan 口名称，通常为 eth1
/// @return
const char *m_wan_interface();
/// @brief 获取 lan 口桥接名称，通常为 br-lan
const char *m_lan_bridge();

typedef struct
{
    // IP mask;
    IP lanIP; // router ip
    uint32_t mask_bits_cnt; // 0~32, 上层会保证其正确性
    uint32_t start; // start host number
    uint32_t limit; // host number limit
    uint32_t leaseTimeSec;
} DhcpCfg;
MError *m_dhcp_get_cfg(DhcpCfg *cfg);
MError *m_dhcp_set_cfg(const DhcpCfg *cfg);
MError *m_dhcp_apply();

/// @brief 解绑网口和桥
void m_dettach_interface_from_bridge(const char *interface, const char *bridge);
/// @brief 绑定网口和桥
void m_attach_interface_to_bridge(const char *interface, const char *bridge);
/// mesh

typedef enum
{
    METNotSet = 0, // 表示没有读到
    // 组网流程上层不需要控制，一些平台也无法控制
    METNodeJoinByWireless, // 从节点从无线口加入
    METNodeJoinByWired,        // 从节点从有线口加入
    METMeshMsg,                // 从mesh 网络发过来的消息
    METNodeLeave,              // 节点从 mesh 网络中离开
} MeshEventType;
typedef struct
{
    MeshEventType type;   // 事件类型
    StructuredMac src_mac; // 事件源。在 mesh 层应该都是以 mac 地址交互。
    union {
        char mesh_msg[1024]; // mesh 消息
    } payload;     // 事件的数据
} MeshEvent;

// 监听 mesh 事件所需要的句柄，完全由底层平台定义。
typedef struct
{
    // 底层 vendor 自己负责对此句柄的操作。
    void *priv;
} MeshEventListener;

/**
 * 底层需要对 listener 中的 priv 进行初始化和释放（如果有的话）.
 */
MError *m_mesh_event_listener_new(MeshEventListener **listener);
void m_mesh_event_listener_free(MeshEventListener *listener);
/// 读取 mesh 事件。
MError *m_mesh_event_listener_read_event(MeshEventListener *listener, MeshEvent *event, uint64_t timeout_ms);
// 从 mesh 网络发送消息。
MError *m_mesh_send_msg(const char *msg, const char *mac);

// 启动 dnstrap。DNS trap 是由底层支持的解析局域网域名的功能。
MError *m_dnstrap_start();

/**
 * @brief 将 file 文件映射到 http 服务的根目录下。
 * 注意：target 目前不支持目录，只支持文件。
 *
 * @param file
 * @param target
 * @return MError*
 */
MError *m_fw_link_file_to_http_server_root(const char *file, const char *target);

// 系统事件
typedef enum
{
    SETWanPlugedIn = 0, // wan 口插入
    SETWanPlugedOut,    // wan 口拔出
    SETNetworkUp,       // 外网连通
    SETNetowrkGone,     // 外网断开
    SETNodeRssiPool,    // rssi pool
    SETNodeRssiGood,    // rssi good
    SETNodeOutOfReach,  // node is gone.
    SETMeshingStart,    // 开始组网
    SETUnknown,
} SystemEventType;

typedef struct
{
    SystemEventType etype;
} SystemEvent;

// 监听系统事件。
MError *m_listen_system_event(void (*handler)(const SystemEvent *event, void *data), void *data);
// 发送一个系统事件
MError *m_fire_system_event(const SystemEvent *event);
MError *m_system_event_run();

typedef struct
{
    IPv4 ip;
    char name[60];
    MacHrCompacted mac;
} StaticIPRule;

typedef struct 
{
    StaticIPRule rules[50];
    uint32_t count;
} StaticIPRules;

/**
 * @brief 静态 ip 设置。
 * todo 似乎放业务层更合理，底层不应该有 name/id 这样的字段
 * @param id 可选，为空表示新增，不为空表示更新。
 * @param rule
 * @return MError*
 */
MError *m_staticip_set(const StaticIPRules *rules);
MError *m_staticip_load_rules(StaticIPRules *rules);
MError *m_staticip_clear();

// upnp
typedef struct
{
    /* data */
    bool enabled;

} UpnpCfg;
MError *m_apply_upnp();
MError *m_get_upnp(UpnpCfg *cfg);
MError *m_update_upnp(const UpnpCfg *cfg);

// typedef struct
// {
//     bool enable;
//     uint32_t port;
//     IP allowed_ips[10];
//     uint32_t ip_cnt;
// } MWwaCfg;

// MError *m_wwa_get_cfg(MWwaCfg *cfg);
// MError *m_wwa_set_cfg(const MWwaCfg *cfg);
// MError *m_wwa_apply();

// todo 就算要实现也应该放到业务层，vendor 不需要实现。
typedef struct
{
    bool enabled; // 整体功能是否开启

    bool wifi_enabled; // wifi冻结是否开启
    bool internet_enabled;
    bool ipv6_enabled;
    bool tr069_enabled;
} FrozenCfg;

// todo 这个功能需要重新设计, vendor 暂时不需要实现
MError *m_frozen_get_cfg(FrozenCfg *cfg);
MError *m_frozen_set_cfg(const FrozenCfg *cfg);

// 生成备份文件，目前都是采用`sysupgrade -b <file>` 来生成的，其它平台需要再看看
MError *m_backup_gen_tar(char *tarFile);

/// @brief 返回一个 merckuos 用于存储数据的工作目录。注意：它需要升级后仍然有效。openwrt 系统上，在 /etc/sysupgrade.conf 中进行配置豁免。
const char *m_get_merckuos_working_dir();

/**
 * tr 系列。目前使用的商业版本实现完全依赖于 openwrt，现在暂时不考虑其它平台支持，后续再进一步抽象。故目前 vendor 不需要实现。
 */
typedef struct
{
    bool enabled;
    struct
    {
        char username[64];
        char password[64];
        char path[128];
        int32_t port;
    } local;
    struct
    {
        char username[64];
        char password[64];
        int32_t interval_sec;
        char url[128];
    } remote;
} MTrSetting;

MError *m_tr_get_cfg(MTrSetting *cfg);
MError *m_tr_set_cfg(const MTrSetting *cfg);
MError *m_tr_apply();

/**
 * @brief 获取当前的生命周期 id。此方法是为了兼容旧版本，供应商不需要实现。
 */
void m_get_lifecycle_id(char id[80]);
/**
 * @brief 绑定 host 到 ip。mercku 目前采用 dnsmasq，鉴于底层使用的软件和版本可能不一致，故将此逻辑暴露到底层。
 * 注：由于我们的用户有定制域名的需要，为了隔离，这里采用接口方式指定。
 */
void m_bind_host(const char *host, const char *ip);

/**
 * @brief 设置网卡的 mtu。要保证重启后仍然有效。
 *
 * @param iface
 * @param mtu
 */
MError *m_set_mtu(IN const char *iface, IN uint32_t mtu);


// m6。目前 沒有時間抽象，先這麼寫，其它產品跳過這個部份的實現即可。
typedef struct {
    SN sn;
    MacHr mac_2g;
    MacHr mac_5g;
} M6ScanNode;
typedef struct {
    M6ScanNode nodes[20];
    int32_t count;
} M6ScanResult;

/**
 * @brief m6 独中，不需要实现
 * 
 * @param candidates 
 * @return MError* 
 */
MError *m_m6_scan_mesh(OUT M6ScanResult *candidates);

// todo
MError *m_sysupgrade(const char *firmware_path);
MError *m_upgrade_status(enum xxx xxx_state);

#endif // __MERCKU_VENDOR_ALL_H__