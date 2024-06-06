#ifndef __NOC_API_H__
#define __NOC_API_H__


#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define SYNC_MSG_VERSION 1

typedef enum AccRole {
  ARRoot,
  /**
   * 非 root 用户
   */
  AROther,
} AccRole;

typedef enum AcsStrategy {
  /**
   * 指定时间段内扫描
   */
  INTIME,
  /**
   * 只在启动时扫描
   */
  ONREBOOT,
} AcsStrategy;

typedef enum ApiRole {
  ARHole = 0,
  ARSuper,
  ARAdmin,
} ApiRole;

typedef enum ApiTxPower {
  Low = 0,
  Medium,
  High,
} ApiTxPower;

typedef enum BackhaulType {
  Wifi2G = 0,
  Wifi5G,
  Ethernet,
  Unknown,
} BackhaulType;

typedef enum Band {
  Band2G = 0,
  Band5G,
  BandWired,
} Band;

typedef enum BandChannelMode {
  BCMAuto,
  BCMManual,
} BandChannelMode;

typedef enum BandsType {
  band_2_4g,
  band_5g,
} BandsType;

typedef enum CmdStatus {
  CSPending,
  CSSuccess,
  CSFailed,
} CmdStatus;

typedef enum CommonMode {
  CMRouter = 1,
  CMBridge,
  CMWirelessBridge,
  CMFree,
  CMBlacklist,
  CMWhitelist,
} CommonMode;

typedef enum CommonParamProtocol {
  CPPTcp,
  CPPUdp,
  CPPTcpUdp,
  /**
   * for vpn
   */
  CPPL2tp,
  CPPPptp,
  CPPOpenvpn,
  CPPWireguard,
} CommonParamProtocol;

typedef enum CommonParamStatus {
  /**
   * for ddns
   */
  CPSPending,
  CPSSuccessful,
  CPSFailed,
  /**
   * for vpn
   */
  CPSConnect,
  CPSDisconnect,
} CommonParamStatus;

typedef enum CommonType {
  CTNotSet,
  CTStatic,
  CTAuto,
  CTPppoe,
  CTSn,
  CTWanStatus,
  CTWanDns,
  CTWanLatency,
} CommonType;

typedef enum DdnsService {
  DSDyndns,
  /**
   * 花生壳
   */
  DSOray,
} DdnsService;

typedef enum DdnsStatus {
  DSPending,
  DSSuccess,
  DSFailed,
} DdnsStatus;

typedef enum DocsisProcedureState {
  DPSNotStarted = 0,
  DPSCompleted,
} DocsisProcedureState;

typedef enum Encrypt {
  OPEN = 0,
  WEP = 1,
  WPA = 2,
  WPA2 = 4,
  WPAWPA2 = 6,
  WAPI = 7,
  WPA3 = 9,
  WPA2WPA3 = 10,
} Encrypt;

typedef enum FirewallRuleWanPingIPLimitMode {
  Free = 0,
  Blacklist,
  Whitelist,
} FirewallRuleWanPingIPLimitMode;

typedef enum InitSSIDStrategyType {
  /**
   * 固定的SSID
   */
  ISSTFixed,
  /**
   * 根据 sn 进行定制
   */
  ISSTSnCompose,
} InitSSIDStrategyType;

typedef enum InitWifiPskBuilder {
  IWPBFixed,
  IWPBScript,
} InitWifiPskBuilder;

typedef enum InitWifiPskEncryptType {
  IWPETNone,
  IWPETWpa2,
} InitWifiPskEncryptType;

typedef enum LANNetType {
  LNTClient,
  LNTServer,
  LNTDisabled,
} LANNetType;

enum MeshBackhaulType {
  MBTWireless2G = 0,
  MBTWireless5G,
  MBTEth,
  MBTUnknown,
};
typedef int32_t MeshBackhaulType;

typedef enum MeshNetworkDiagnoseParamType {
  MNDPTWanStatus = 0,
  MNDPTWanDns,
  MNDPTWanLatency,
} MeshNetworkDiagnoseParamType;

typedef enum MeshNodeState {
  /**
   * 正常
   */
  MNSNormal = 0,
  MNSSignalPoor,
  /**
   * 正在组网
   */
  MNSMeshing,
  /**
   * 升级中
   */
  MNSUpgrading,
  MNSUpgradeFailed,
  /**
   * 正在下载固件
   */
  MNSDownloadingFW,
  MNSDownloadFWFailed,
  MNSInstallingFW,
  MNSInstallFWFailed,
  MNSRebooting,
  MNSResetting,
  MNSOffline,
  MNSNum,
} MeshNodeState;

typedef enum MeshToolsExecuteParamTool {
  PING = 0,
  TRACEROUTE,
  NSLOOKUP,
} MeshToolsExecuteParamTool;

typedef enum MeshToolsExecuteResultStatus {
  MTERSDone = 0,
  MTERSExecuting,
  MTERSFailed,
} MeshToolsExecuteResultStatus;

typedef enum MeshWanSpeedTestResultStatus {
  MWSTRSSuccess = 0,
  MWSTRSFailed,
  MWSTRSRunning,
} MeshWanSpeedTestResultStatus;

typedef enum MeshWanStatus {
  MWSSUnlinked = 0,
  /**
   * 已插线，但是不能联网
   */
  MWSSLinked,
  /**
   * 能联网
   */
  MWSSConnected,
} MeshWanStatus;

typedef enum Method {
  InvalidMethod,
  router_is_initial,
  RouterReport,
  /**
   * for empty case
   */
  mesh_node_reboot,
  node_reboot,
  mesh_node_reset,
  mesh_node_delete,
  node_reset,
  RESPONSE,
  mesh_config_wifi_update,
  mesh_region_get,
  mesh_guestwifi_update,
  /**
   * 获取 mesh guest wifi 信息
   */
  mesh_guestwifi_get,
  mesh_config_wifi_time_limit_get,
  mesh_tools_execute,
  router_wwa_update,
  router_wwa_get,
  mesh_portfw_add,
  mesh_portfw_update,
  mesh_portfw_delete,
  /**
   * 获取端口转发配置
   */
  mesh_portfw_get,
  mesh_config_lan_net_update,
  /**
   * 获取 dhcp 配置
   */
  mesh_info_lan_net_get,
  mesh_config_timezone_update,
  /**
   * 获取时区信息
   */
  mesh_info_timezone_get,
  mesh_region_update,
  mesh_region_supported_get,
  /**
   * 更新主路由 mode
   */
  mesh_mode_update,
  /**
   * 获取 mesh mode 信息
   */
  mesh_mode_get,
  mesh_node_get,
  /**
   * 获取 mesh wifi 信息
   */
  mesh_meta_get,
  /**
   * 获取 mesh 限速信息
   */
  mesh_device_speed_limit_get,
  /**
   * 配置 mesh 限速信息
   */
  mesh_device_speed_limit_update,
  /**
   * 获取 mesh 黑名单
   */
  mesh_device_parent_control_get,
  /**
   * 启用 mesh 黑名单
   */
  mesh_device_parent_control_update,
  /**
   * 添加 mesh 黑名单
   */
  mesh_device_parent_control_add,
  /**
   * 删除 mesh 黑名单
   */
  mesh_device_parent_control_delete,
  /**
   * 获取 mesh ddns 信息
   */
  mesh_ddns_get,
  /**
   * new setting
   */
  mesh_wps_get,
  mesh_logs_setting_get,
  /**
   * 配置 mesh ddns 信息
   */
  mesh_ddns_update,
  mesh_vpn_info_get,
  mesh_vpn_get,
  mesh_vpn_add,
  mesh_vpn_update,
  mesh_vpn_delete,
  vpn_info_get,
  mesh_vpn_config_update,
  /**
   * 获取 dmz 信息
   */
  mesh_dmz_get,
  /**
   * 更新 dmz 信息
   */
  mesh_dmz_update,
  mesh_config_admin_update,
  /**
   * 添加黑名单
   */
  mesh_blacklist_add,
  /**
   * 获取黑名单
   */
  mesh_blacklist_get,
  /**
   * 删除黑名单
   */
  mesh_blacklist_delete,
  mesh_wan_speed_test,
  /**
   * 发起测速，并获取 wan 限速信息
   */
  mesh_wan_speed_test_report,
  /**
   * 获取自动升级配置
   */
  mesh_auto_upgrade_get,
  /**
   * 设置自动升级配置
   */
  mesh_auto_upgrade_set,
  mesh_node_upgradability_get,
  iot_keys_certs_urls,
  mesh_config_update,
  router_initialize,
  router_meta_get,
  mesh_device_count_get,
  mesh_info_wan_net_get,
  mesh_info_wan_stats_get,
  mesh_wan_status_get,
  /**
   * 获取当前连接的设备
   */
  mesh_device_get,
  mesh_info_wan_net_ipv6_get,
  mesh_channel_supported_get,
  mesh_device_update,
  mesh_node_add,
  mesh_node_new_info,
  router_firmware_check,
  mesh_led_time_limit_get,
  mesh_led_time_limit_update,
  mesh_config_wan_net_update,
  mesh_node_upgrade,
  node_upgrade,
  mesh_config_wan_net_ipv6_update,
  mesh_rsvdip_get,
  mesh_rsvdip_add,
  mesh_rsvdip_update,
  mesh_rsvdip_delete,
  mesh_node_update,
  node_update,
  mesh_network_reboot,
  node_network_reboot,
  mesh_upnp_enabled_get,
  mesh_upnp_enabled_update,
  mesh_info_wan_mac_get,
  mesh_config_wan_mac_update,
  mesh_info_firewall_get,
  mesh_config_firewall_update,
  router_config_frozen_get,
  router_config_frozen_update,
  router_config_backup_create,
  router_config_backup_restore,
  mesh_config_wifi_time_limit_update,
  mesh_device_time_limit_get,
  mesh_syslog_enabled_get,
  router_password_check,
  mesh_info_get,
  mesh_network_diagnose,
  router_tr069_get,
  router_tr069_update,
  firmware_get,
  factory_cmd_execute,
  router_login,
  request_get,
  router_is_login,
  mesh_apclient_scan,
  mesh_band_get,
  mesh_band_update,
  mesh_node_scan,
  docsis_cm_status_get,
  docsis_mta_status_get,
} Method;

typedef enum Mode {
  AP,
  MESH,
  APMESH,
} Mode;

typedef enum MtkDumpsTopologyInformationBhInfoConnectedType {
  MDTIBICT24G = 0,
  MDTIBICT5G,
  MDTIBICTEth,
} MtkDumpsTopologyInformationBhInfoConnectedType;

typedef enum MtkDumpsTopologyInformationDistance {
  MDTID0 = 0,
  MDTID1,
  MDTID2,
  MDTID3,
  MDTID4,
  MDTID5,
  MDTID6,
  MDTID7,
  MDTID8,
  MDTID9,
} MtkDumpsTopologyInformationDistance;

typedef enum MtkDumpsTopologyInformationMeshRole {
  MDTIMRController,
  MDTIMRAgent,
} MtkDumpsTopologyInformationMeshRole;

typedef enum MtkDumpsTopologyInformationRadioBssInfoStaBhStaEnabled {
  MDTIRBISBEFalse = 0,
  MDTIRBISBETure,
} MtkDumpsTopologyInformationRadioBssInfoStaBhStaEnabled;

typedef enum NetInfo6Family {
  NI6FIpv4,
  NI6FIpv6,
} NetInfo6Family;

typedef enum NocRouterCommandResponseBodyMethod {
  NRCRBMResponse = 0,
} NocRouterCommandResponseBodyMethod;

typedef enum NodeUpgradeParamFWSource {
  NUPFSLocal,
} NodeUpgradeParamFWSource;

typedef enum NodeWorkRole {
  NWRNotSet = 0,
  NWRMaster = 1,
  NWRSlave = 2,
} NodeWorkRole;

typedef enum PCMode {
  PCFree = 0,
  PCBlacklist,
  PCWhitelist,
} PCMode;

typedef enum PortFWProtocol {
  PFPTcp = 0,
  PFPUdp,
  PFPTcpUdp,
} PortFWProtocol;

typedef enum RWanProfileCfgProfileType {
  RWanProfileCfgProfileTypeDhcp,
  RWanProfileCfgProfileTypePppoe,
} RWanProfileCfgProfileType;

typedef enum ReportMeshStatus {
  RMSOnline,
  RMSOffline,
} ReportMeshStatus;

typedef enum ReportMethod {
  igd_inform,
} ReportMethod;

enum ResponseErrorCode {
  RECOk = 0,
  /**
   * 10xxxx, 内部错误(没有对应翻译的、只在调试阶段出现的，如：错误的 json 格式), 其余都是外部错误
   */
  RECArgRequired = 100200,
  RECInvalidArg = 100208,
  RECInvalidJson = 100209,
  RECUnknownMethod = 100299,
  RECUnknown = 109999,
  /**
   * 20xxxx, 通用错误
   */
  RECConnectTimeout = 200001,
  RECAuthFailed = 200101,
  RECNodesLimit = 200501,
  RECSpeedTestFailed = 200701,
  RECUpgradeFailed = 200703,
  RECPingFailed = 200704,
  /**
   * 30xxxx, mercku server error
   */
  RECNotRegistered = 300101,
  RECWrongPassword = 300102,
  RECAccountExsted = 300104,
  RECEmailSchema = 300201,
  RECUnknownSn = 300401,
  /**
   * 60xxxx, router error
   * 外网不通
   */
  RECRNWan = 600101,
  /**
   * 条目已存在
   */
  RECItemExisting = 600200,
  RECRouterRebooting = 600401,
  RECRouterUpgrading = 600402,
  /**
   * 无效固件
   */
  RECBrokenFW = 600403,
  /**
   * 节点升级过程中获取镜像失败
   */
  RECUpgradeTransferFWFailed = 600404,
  RECNetworkRestarting = 600405,
  /**
   * 当前用户权限不够
   */
  RECAuthorityLimit = 600407,
  /**
   *不能在同一子网
   */
  RECIPUltralimit = 600706,
  /**
   *IP不能相同
   */
  RECIPConflict = 600707,
  /**
   *服务器错误
   */
  RECRnServer = 600103,
};
typedef int32_t ResponseErrorCode;

typedef enum RouterConfigFrozenGetResultSupportedConfig {
  RCFGRSCWifi,
  RCFGRSCInternet,
  RCFGRSCIpv6,
  RCFGRSCTr069,
} RouterConfigFrozenGetResultSupportedConfig;

typedef enum RouterMode {
  /**
   * 主路由
   */
  RMRouter = 1,
  /**
   * 有线桥接
   */
  RMBridge,
  /**
   * 无线桥接
   */
  RMWirelessBridge,
} RouterMode;

typedef enum RouterStatus {
  RSOnline,
  RSOffline,
  RSRebooting,
  RSUpgrading,
  RSDownloading,
  RSInstalling,
} RouterStatus;

typedef enum ScheduleWeekday {
  /**
   * for terminal use
   */
  Invalid = 0,
  Sunday,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
} ScheduleWeekday;

typedef enum SessionRole {
  SRSuper = 0,
  SRAdmin,
  SRGuest,
} SessionRole;

typedef enum StaNetworkType {
  SNTPrimary = 1,
  SNTGuest,
} StaNetworkType;

typedef enum StaOnlineStatus {
  SOSOnline = 0,
  SOSOffline,
} StaOnlineStatus;

typedef enum VlanPortType {
  VPTWan = 0,
  VPTLan,
  VPTWifi,
} VlanPortType;

typedef enum VpnConfigStatus {
  VCSConnect,
  VCSDisconnect,
} VpnConfigStatus;

typedef enum VpnConnectStatus {
  VCSConnected,
  VCSConnecting,
  VCSDisconnected,
  VCSDisconnecting,
} VpnConnectStatus;

typedef enum VpnProtocol {
  VPNotSet = 0,
  VPL2tp,
  VPPptp,
  VPOpenvpn,
  VPWireguard,
} VpnProtocol;

typedef enum Wan6Mode {
  W6MStatic = 0,
  W6MAuto,
  W6MPppoe,
} Wan6Mode;

typedef enum WanMode {
  WMStatic = 0,
  WMDhcp,
  WMPppoe,
} WanMode;

typedef enum WanMode6 {
  WM6Static = 0,
  WM6Dhcp,
  WM6Pppoe,
} WanMode6;

typedef char *FFIError;

/**
 * 返回值结构体。
 */
typedef struct Response {
  /**
   * 返回码
   */
  ResponseErrorCode code;
  /**
   * 可选的返回信息
   */
  char *msg;
} Response;

typedef struct Meta {
  int32_t api_version;
  enum ApiRole api_role;
  bool is_async;
  char *response_topic;
  char *req_id;
} Meta;

/**
 * 由于目前的接口设计中，大量复用了相同属性，甚至同名属性的名称还不一样。这导致在 rust 反序列化时，同名属性会相互影响。所以这里搞了一个 CommonParam，主要目的就是放这些冲突的属性，在具体的处理过程中，需要把这些值拷贝到具体的结构体中。
 */
typedef struct CommonParam {
  /**
   * sn, 不传或者空表示所有设备
   */
  char **node_ids;
  enum CommonMode mode;
  enum CommonType typ;
  char *id;
  char *name;
  char *mac;
  char *ip;
  char *username;
  char *password;
  char *domain;
  enum CommonParamStatus status;
  /**
   * bool, 双频合一
   */
  bool smart_connect;
  bool enabled;
  enum ScheduleWeekday **schedule;
  char *sn;
  enum CommonParamProtocol protocol;
} CommonParam;

typedef struct FirewallRuleWanPingIPLimit {
  char **ip_list;
  enum FirewallRuleWanPingIPLimitMode mode;
} FirewallRuleWanPingIPLimit;

typedef struct FirewallRuleWanPing {
  bool enabled;
  struct FirewallRuleWanPingIPLimit ip_limit;
} FirewallRuleWanPing;

typedef struct FirewallRuleWan {
  bool dos;
  struct FirewallRuleWanPing ping;
} FirewallRuleWan;

typedef struct FirewallRule {
  struct FirewallRuleWan wan;
} FirewallRule;

typedef struct MeshInfoWanIpv6Addr {
  char *ip;
  uint32_t prefix_length;
} MeshInfoWanIpv6Addr;

typedef struct MeshInfoWanIpv6PPPoE {
  bool share_ipv4_credentials;
  char *account;
  char *password;
  struct MeshInfoWanIpv6Addr **dns;
} MeshInfoWanIpv6PPPoE;

typedef struct MeshInfoWanIpv6Auto {
  struct MeshInfoWanIpv6Addr **dns;
} MeshInfoWanIpv6Auto;

typedef struct MeshInfoWanIpv6NetInfo {
  char *family;
  struct MeshInfoWanIpv6Addr **address;
  struct MeshInfoWanIpv6Addr *gateway;
  struct MeshInfoWanIpv6Addr **dns;
} MeshInfoWanIpv6NetInfo;

typedef struct MeshInfoWanIpv6Static {
  struct MeshInfoWanIpv6NetInfo *netinfo;
} MeshInfoWanIpv6Static;

typedef struct MeshInfoWanIpv6Config {
  enum Wan6Mode typ;
  /**
   * type == pppoe
   */
  struct MeshInfoWanIpv6PPPoE *pppoe;
  /**
   * type == auto
   */
  struct MeshInfoWanIpv6Auto *auto_;
  struct MeshInfoWanIpv6Static *static_;
} MeshInfoWanIpv6Config;

typedef struct MeshInfoWanIpv6Info {
  bool enabled;
  struct MeshInfoWanIpv6Config *config6;
  struct MeshInfoWanIpv6NetInfo *netinfo;
} MeshInfoWanIpv6Info;

typedef struct MeshInfoWanNetGetResultPPPoE {
  char *account;
  char *password;
  char **dns;
} MeshInfoWanNetGetResultPPPoE;

typedef struct MeshInfoWanNetGetResultDhcp {
  char **dns;
} MeshInfoWanNetGetResultDhcp;

typedef struct NetInfo {
  char *ip;
  char *mask;
  char *gateway;
  char **dns;
} NetInfo;

typedef struct MeshInfoWanNetGetResultStatic {
  struct NetInfo netinfo;
} MeshInfoWanNetGetResultStatic;

typedef struct VlanPortPort {
  /**
   * hardware port id, int。 M2:0, M6/M6A:4
   */
  int32_t id;
  char *name;
  enum VlanPortType typ;
} VlanPortPort;

typedef struct VlanPort {
  struct VlanPortPort port;
  bool tagged;
} VlanPort;

typedef struct Vlan {
  int32_t id;
  bool enabled;
  int32_t priority;
  bool is_bridged;
  char *name;
  struct VlanPort **ports;
} Vlan;

typedef struct MeshConfigWanNetUpdateParam {
  enum WanMode wan_type;
  /**
   * type == pppoe
   */
  struct MeshInfoWanNetGetResultPPPoE *pppoe;
  /**
   * type == dhcp
   */
  struct MeshInfoWanNetGetResultDhcp *dhcp;
  struct MeshInfoWanNetGetResultStatic *static_;
  struct Vlan **vlan;
} MeshConfigWanNetUpdateParam;

typedef struct MeshVpnConfigUpdateParam {
  enum VpnConfigStatus status;
  char *vpn_id;
} MeshVpnConfigUpdateParam;

typedef struct MeshDeviceUpdateParamDevice {
  char *mac;
  char *name;
} MeshDeviceUpdateParamDevice;

typedef struct MeshDeviceUpdateParam {
  struct MeshDeviceUpdateParamDevice device;
} MeshDeviceUpdateParam;

typedef struct Acs {
  enum AcsStrategy switch_strategy;
  char *begin_time;
  char *end_time;
  /**
   * 扫描间隔，单位分钟
   */
  int32_t interval;
  /**
   * 当前网速小于此阈值时可进行信道切换，单位：bps
   */
  int32_t traffic_threshold;
} Acs;

typedef struct BandChannel {
  enum BandChannelMode mode;
  /**
   * 信道号, BCMManual模式下必填
   */
  int32_t number;
  /**
   * 频宽，MHz，可选。2.4g可选的有20、40 ，默认的40;5g可选的有20、40、80，默认的80.
   */
  int32_t bandwidth;
  struct Acs *acs;
} BandChannel;

typedef struct MeshConfigWifiUpdateParamBand {
  char *ssid;
  char *password;
  enum Encrypt *encrypt;
  bool *enable;
  bool *hidden;
  enum Mode *mode;
  struct Acs *acs;
  struct BandChannel *channel;
} MeshConfigWifiUpdateParamBand;

typedef struct MeshConfigWifiUpdateParamBands {
  struct MeshConfigWifiUpdateParamBand band_2_4g;
  struct MeshConfigWifiUpdateParamBand band_5g;
} MeshConfigWifiUpdateParamBands;

typedef struct MeshConfigWifiUpdateParam {
  struct MeshConfigWifiUpdateParamBands *bands;
  /**
   * 双频合一，默认为true
   */
  bool *smart_connect;
  enum ApiTxPower *tx_power;
  bool *compatibility_mode;
  bool *hidden;
} MeshConfigWifiUpdateParam;

typedef struct MeshConfigGuestWifiUpdateParamBand {
  char *ssid;
  char *password;
  enum Encrypt *encrypt;
  bool hidden;
} MeshConfigGuestWifiUpdateParamBand;

typedef struct MeshConfigGuestWifiUpdateParamBands {
  struct MeshConfigGuestWifiUpdateParamBand band_2_4g;
  struct MeshConfigGuestWifiUpdateParamBand band_5g;
} MeshConfigGuestWifiUpdateParamBands;

typedef struct MeshGuestWifiUpdateParam {
  char *id;
  bool enabled;
  /**
   *integer, 访客网路开启时长(单位:s), -1 表示永久开启
   */
  int32_t duration;
  struct MeshConfigGuestWifiUpdateParamBands bands;
  /**
   * bool, 双频合一
   */
  bool smart_connect;
} MeshGuestWifiUpdateParam;

typedef struct MeshConfigWifiScheduleUpParam {
  char *id;
  char *time_begin;
  char *time_end;
  enum ScheduleWeekday **schedule;
  bool enabled;
  enum BandsType **bands;
} MeshConfigWifiScheduleUpParam;

typedef struct JobParam {
  char *host;
} JobParam;

typedef struct MeshToolsExecuteParam {
  enum MeshToolsExecuteParamTool job_type;
  struct JobParam job_params;
} MeshToolsExecuteParam;

typedef struct RouterWwaUpdateParam {
  bool enabled;
  int32_t port;
  char **allowed_ip;
} RouterWwaUpdateParam;

typedef struct PortRule {
  int32_t from;
  int32_t to;
} PortRule;

typedef struct PortRulePair {
  char *ip;
  struct PortRule port;
} PortRulePair;

typedef struct MeshPortfwUpdateAddParam {
  char *id;
  char *name;
  bool enabled;
  struct PortRulePair local;
  struct PortRulePair remote;
  enum PortFWProtocol protocol;
} MeshPortfwUpdateAddParam;

typedef struct MeshPortfwDeleteParam {
  char **portfw_ids;
} MeshPortfwDeleteParam;

typedef struct MeshConfigLanNetUpdateParamDhcpServerNetInfo {
  char *ip;
  char *mask;
} MeshConfigLanNetUpdateParamDhcpServerNetInfo;

typedef struct MeshConfigLanNetUpdateParamDhcpServer {
  char *ip_start;
  char *ip_end;
  /**
   * seconds
   */
  int32_t lease;
  char *domain;
  struct MeshConfigLanNetUpdateParamDhcpServerNetInfo netinfo;
} MeshConfigLanNetUpdateParamDhcpServer;

typedef struct MeshConfigLanNetUpdateParam {
  enum LANNetType typ;
  struct MeshConfigLanNetUpdateParamDhcpServer dhcp_server;
} MeshConfigLanNetUpdateParam;

typedef struct Timezone {
  /**
   * int, [-12, 12]，GMT+8 取值为 -8，GMT-8 取值为 +8，以此类推
   */
  int32_t offset;
  /**
   * int, 相同时区城市的序号，序号从 1 开始。
   */
  int32_t position;
} Timezone;

typedef struct SpeedLimit {
  uint32_t up;
  uint32_t down;
  bool enabled;
} SpeedLimit;

typedef struct MeshDeviceSpeedLimitUpdateParam {
  char *mac;
  struct SpeedLimit speed_limit;
} MeshDeviceSpeedLimitUpdateParam;

typedef struct ParentControlUpdateParam {
  enum PCMode mode;
  char **hosts;
  char *mac;
} ParentControlUpdateParam;

typedef struct MeshDdnsUpdateParam {
  bool enabled;
  enum DdnsService service;
  enum DdnsStatus status;
  char *domain;
  char *username;
  char *password;
} MeshDdnsUpdateParam;

typedef struct VpnPptp {
  bool mppe;
  bool mppc;
} VpnPptp;

typedef struct VpnOpenvpn {
  char *url;
} VpnOpenvpn;

typedef struct WireguardCfgPeer {
  char *public_key;
  char *preshared_key;
  char *endpoint_host;
  uint32_t endpoint_port;
  char **allowed_ips;
  uint32_t persistent_keepalive;
  bool route_allowed_ips;
} WireguardCfgPeer;

typedef struct WireguardCfgInterface {
  char *private_key;
  char **addresses;
  uint32_t listen_port;
  uint32_t mtu;
} WireguardCfgInterface;

typedef struct WireguardCfg {
  struct WireguardCfgPeer **peers;
  struct WireguardCfgInterface interface;
} WireguardCfg;

typedef struct MeshVpnAddParam {
  char *id;
  char *name;
  enum VpnProtocol protocol;
  char *server;
  char *username;
  char *password;
  struct VpnPptp pptp;
  struct VpnOpenvpn *openvpn;
  struct WireguardCfg *wireguard;
} MeshVpnAddParam;

typedef struct MeshVpnDeleteParam {
  char **vpn_ids;
} MeshVpnDeleteParam;

typedef struct Dmz {
  bool enabled;
  char *ip;
} Dmz;

typedef struct BLSta {
  char *name;
  char *mac;
} BLSta;

typedef struct MeshBlacklistAddParam {
  struct BLSta **devices;
} MeshBlacklistAddParam;

typedef struct MeshBlacklistDeleteParam {
  char **macs;
} MeshBlacklistDeleteParam;

typedef struct MeshWanSpeedTestParam {
  bool force;
} MeshWanSpeedTestParam;

typedef struct MeshModeUpdateParam {
  enum RouterMode mode;
} MeshModeUpdateParam;

typedef struct ScheduleTime {
  int32_t hour;
  int32_t minute;
} ScheduleTime;

typedef struct MeshAutoUpgradeSetParam {
  bool enabled;
  /**
   * 以 Invalid 结尾
   */
  enum ScheduleWeekday **schedule;
  struct ScheduleTime time;
} MeshAutoUpgradeSetParam;

typedef struct StaGetParamFilter {
  enum StaNetworkType network_type;
  enum StaOnlineStatus **online_status;
} StaGetParamFilter;

typedef struct MeshDeviceGetParam {
  struct StaGetParamFilter **filters;
} MeshDeviceGetParam;

typedef struct MeshDeviceTimeLimitGetParam {
  char *mac;
} MeshDeviceTimeLimitGetParam;

typedef struct MeshRsvdipDeleteParam {
  char **ids;
} MeshRsvdipDeleteParam;

typedef struct VpnConfig {
  bool enabled;
  char *default_vpn;
} VpnConfig;

typedef struct ParamGetCertUrls {
  char *sn;
  char *mac;
  char *lifecycle_id;
} ParamGetCertUrls;

typedef struct TimeLimit {
  bool enabled;
  char *id;
  struct ScheduleTime time_begin;
  struct ScheduleTime time_end;
  enum ScheduleWeekday **schedule;
} TimeLimit;

typedef struct TimeLimitDelParam {
  char *mac;
  char **ids;
} TimeLimitDelParam;

typedef struct MeshRegionUpdateParam {
  uint32_t region_id;
} MeshRegionUpdateParam;

typedef struct MeshConfigUpdateParamConfigWifiBand {
  char *ssid;
  char *password;
  enum Encrypt encrypt;
} MeshConfigUpdateParamConfigWifiBand;

typedef struct MeshConfigUpdateParamConfigWifiBands {
  struct MeshConfigUpdateParamConfigWifiBand g24;
  struct MeshConfigUpdateParamConfigWifiBand g5;
} MeshConfigUpdateParamConfigWifiBands;

typedef struct MeshConfigUpdateParamConfigWifi {
  struct MeshConfigUpdateParamConfigWifiBands bands;
  /**
   * 实际上，这个 smart_connect 是不需要的，因为它是由 2.4G 和 5G 的 ssid 相同来判断的。
   */
  bool smart_connect;
} MeshConfigUpdateParamConfigWifi;

typedef struct MeshConfigUpdateParamConfigAdmin {
  char *password;
} MeshConfigUpdateParamConfigAdmin;

typedef struct MeshConfigUpdateParamConfig {
  struct MeshConfigUpdateParamConfigWifi wifi;
  struct MeshConfigUpdateParamConfigAdmin admin;
  uint32_t region_id;
} MeshConfigUpdateParamConfig;

typedef struct MeshConfigUpdateParam {
  struct MeshConfigUpdateParamConfig *config;
} MeshConfigUpdateParam;

typedef struct MeshConfigAdminUpdateParam {
  char *username;
  char *password;
  bool passwd_crypt;
} MeshConfigAdminUpdateParam;

typedef struct RouterMacs {
  char *lan;
  char *wan;
  char *main2_4;
  char *main5;
  char *guest2_4;
  char *guest5;
} RouterMacs;

typedef struct RouterModelVersion {
  /**
   * 硬件版本号，sn 第 10 位（J位）
   */
  char *id;
  char *name;
} RouterModelVersion;

typedef struct RouterModel {
  /**
   * 路由器型号，sn 的前两个字符
   */
  char *id;
  char *name;
  char *description;
  struct RouterModelVersion version;
} RouterModel;

typedef struct WebUIRouterFwVersion {
  char *current;
  char *latest;
} WebUIRouterFwVersion;

typedef struct WebUIRouterNeighbor {
  char *sn;
  char *mac;
  int32_t rssi;
  enum BackhaulType backhaul_type;
} WebUIRouterNeighbor;

typedef struct DeviceConnectedStatus {
  enum StaNetworkType typ;
  char *guest_id;
} DeviceConnectedStatus;

typedef struct Speed {
  uint32_t up;
  uint32_t down;
} Speed;

typedef struct Traffic {
  uint32_t ul_bytes;
  uint32_t dl_bytes;
} Traffic;

typedef struct DeviceOnlineInfo {
  /**
   * 当前是否正连接
   */
  bool connected;
  struct Speed realtime_speed;
  struct Traffic traffic;
  char *ssid;
  enum Band band;
  uint64_t online_duration_sec;
  int32_t rssi;
  uint32_t negotiation_rate_bps;
  uint32_t channel;
} DeviceOnlineInfo;

typedef struct Station {
  char *mac;
  char *name;
  struct DeviceConnectedStatus connected_network;
  char *ip;
  struct DeviceOnlineInfo online_info;
} Station;

typedef struct WebUIRouter {
  char *sn;
  char *ip;
  char *name;
  struct RouterMacs mac;
  struct RouterModel model;
  struct WebUIRouterFwVersion version;
  bool is_gw;
  enum RouterStatus status;
  struct NetInfo *lan;
  struct WebUIRouterNeighbor **neighbors;
  struct Station **stations;
  /**
   * 启动时间
   */
  uint32_t uptime_sec;
} WebUIRouter;

typedef struct MeshNodeGetResult {
  struct WebUIRouter **routers;
} MeshNodeGetResult;

typedef struct MeshNodeUpgradeParam {
  bool local;
  char **node_ids;
} MeshNodeUpgradeParam;

typedef struct MeshLedTimeLimitUpdateParam {
  bool enabled;
  struct ScheduleTime *begin_time;
  struct ScheduleTime *end_time;
} MeshLedTimeLimitUpdateParam;

typedef struct Ipv6 {
  char *ip;
  int32_t prefix_length;
} Ipv6;

typedef struct MeshConfigWanNetIpv6UpdateParamIpv6CfgPPPoE {
  /**
   * 是否使用 ipv4 账号
   */
  bool share_ipv4_credentials;
  char *account;
  char *password;
  struct Ipv6 **dns;
} MeshConfigWanNetIpv6UpdateParamIpv6CfgPPPoE;

typedef struct MeshConfigWanNetIpv6UpdateParamIpv6CfgAuto {
  struct Ipv6 **dns;
} MeshConfigWanNetIpv6UpdateParamIpv6CfgAuto;

typedef struct NetInfo6 {
  enum NetInfo6Family family;
  struct Ipv6 **address;
  struct Ipv6 *gateway;
  struct Ipv6 **dns;
} NetInfo6;

typedef struct MeshConfigWanNetIpv6UpdateParamIpv6CfgStatic {
  struct NetInfo6 *netinfo;
} MeshConfigWanNetIpv6UpdateParamIpv6CfgStatic;

typedef struct MeshConfigWanNetIpv6UpdateParamIpv6Cfg {
  enum WanMode6 typ;
  struct MeshConfigWanNetIpv6UpdateParamIpv6CfgPPPoE *pppoe;
  struct MeshConfigWanNetIpv6UpdateParamIpv6CfgAuto *auto_;
  struct MeshConfigWanNetIpv6UpdateParamIpv6CfgStatic *static_;
} MeshConfigWanNetIpv6UpdateParamIpv6Cfg;

typedef struct MeshConfigWanNetIpv6UpdateParam {
  bool enabled;
  struct MeshConfigWanNetIpv6UpdateParamIpv6Cfg *config6;
} MeshConfigWanNetIpv6UpdateParam;

typedef struct NodeUpgradeParam {
  char *fw_url;
  enum NodeUpgradeParamFWSource source;
} NodeUpgradeParam;

typedef struct MeshRsvdipUpdateParam {
  char *id;
  char *name;
  char *ip;
  char *mac;
} MeshRsvdipUpdateParam;

typedef struct MeshNetworkRebootParam {
  char **node_ids;
  uint32_t recovery_time_sec;
} MeshNetworkRebootParam;

typedef struct MeshNodeUpdateParamData {
  char *name;
} MeshNodeUpdateParamData;

typedef struct MeshNodeUpdateParam {
  char *sn;
  struct MeshNodeUpdateParamData data;
} MeshNodeUpdateParam;

typedef struct NodeUpdateParam {
  char *name;
} NodeUpdateParam;

typedef struct MeshUpnpEnabledUpdateParam {
  bool enabled;
} MeshUpnpEnabledUpdateParam;

typedef struct MeshConfigWanMacUpdateParam {
  char *mac;
} MeshConfigWanMacUpdateParam;

typedef struct RouterConfigFrozenUpdateParam {
  bool enabled;
  enum RouterConfigFrozenGetResultSupportedConfig **configs;
} RouterConfigFrozenUpdateParam;

typedef struct MeshNodeDeleteParamNodeMac {
  char *g2;
  char *g5;
} MeshNodeDeleteParamNodeMac;

typedef struct MeshNodeDeleteParamNode {
  char *sn;
  struct MeshNodeDeleteParamNodeMac mac;
} MeshNodeDeleteParamNode;

typedef struct MeshNodeDeleteParam {
  struct MeshNodeDeleteParamNode *node;
} MeshNodeDeleteParam;

typedef struct RouterPasswordCheckParam {
  char *admin_password;
  char *sn;
} RouterPasswordCheckParam;

typedef struct MeshNetworkDiagnoseParamData {
  char *host;
} MeshNetworkDiagnoseParamData;

typedef struct MeshNetworkDiagnoseParam {
  enum MeshNetworkDiagnoseParamType typ;
  struct MeshNetworkDiagnoseParamData *params;
} MeshNetworkDiagnoseParam;

typedef struct TrSettingsRemote {
  char *username;
  int32_t interval_sec;
  char *url;
  char *password;
} TrSettingsRemote;

typedef struct TrSettingsLocal {
  char *path;
  char *username;
  char *password;
  int32_t port;
} TrSettingsLocal;

typedef struct RouterTr069UpdateParam {
  bool enabled;
  /**
   * router上报到远端的信息
   */
  struct TrSettingsRemote *remote;
  /**
   * 远端获取router信息的地址
   */
  struct TrSettingsLocal *local;
} RouterTr069UpdateParam;

typedef struct FirmwareGetParam {
  struct RouterModel *model;
  char **sns;
} FirmwareGetParam;

typedef struct RouterLoginParam {
  char *password;
} RouterLoginParam;

typedef struct RequestGetParam {
  char *request_ip;
} RequestGetParam;

typedef struct RouterIsLoginParam {
  char *session;
} RouterIsLoginParam;

typedef struct MeshInfoGetParam {
  char *mesh_id;
} MeshInfoGetParam;

typedef struct FactoryCmdExecuteParam {
  char *cmd;
  char *mesh_id;
  char *sn;
  char *id;
} FactoryCmdExecuteParam;

typedef struct Param {
  /**
   * 共用参数，解决一些命令的属性复用的情况，主要是 v1 的设计导致反序列化失败。
   * 涉及的方法：
   */
  struct CommonParam *common;
  struct Response *response;
  struct FirewallRule *mesh_config_firewall_update;
  struct MeshInfoWanIpv6Info *mesh_config_wan6_net_update;
  struct MeshConfigWanNetUpdateParam *mesh_config_wan_net_update;
  /**
   * VPN_CONFIG_UPDATE
   */
  struct MeshVpnConfigUpdateParam *mesh_vpn_config_update;
  struct MeshDeviceUpdateParam *mesh_device_update;
  /**
   * for CONFIG_UPDATE_WIFI
   */
  struct MeshConfigWifiUpdateParam *mesh_config_wifi_update;
  struct MeshGuestWifiUpdateParam *mesh_guestwifi_update;
  struct MeshConfigWifiScheduleUpParam *mesh_config_wifi_time_limit_update;
  /**
   * for TOOLS_EXECUTE
   */
  struct MeshToolsExecuteParam *mesh_tools_execute;
  /**
   * for WWA_UPDATE
   */
  struct RouterWwaUpdateParam *router_wwa_update;
  struct MeshPortfwUpdateAddParam *mesh_portfw_update;
  struct MeshPortfwDeleteParam *mesh_portfw_delete;
  /**
   * for CONFIG_UPDATE_LAN_NET
   */
  struct MeshConfigLanNetUpdateParam *mesh_config_lan_net_update;
  /**
   * for CONFIG_UPDATE_TIMEZONE
   */
  struct Timezone *timezone;
  /**
   * DEVICE_SPEED_LIMIT_UPDATE
   */
  struct MeshDeviceSpeedLimitUpdateParam *mesh_device_speed_limit_update;
  /**
   * DEVICE_SPEED_LIMIT_GET/DEVICE_PARENT_CONTROL_GET/DEVICE_PARENT_CONTROL_GET
   * DEVICE_PARENT_CONTROL_UPDATE/DEVICE_PARENT_CONTROL_ADD/DEVICE_PARENT_CONTROL_DELETE
   */
  struct ParentControlUpdateParam *parent_control;
  /**
   * DDNS_UPDATE
   */
  struct MeshDdnsUpdateParam *mesh_ddns_update;
  struct MeshVpnAddParam *mesh_vpn_add;
  /**
   * VPN_DELETE
   */
  struct MeshVpnDeleteParam *mesh_vpn_delete;
  struct Dmz *dmz_up;
  /**
   * CONFIG_ADMIN_UPDATE
   * BlacklistAdd
   */
  struct MeshBlacklistAddParam *mesh_blacklist_add;
  /**
   * BlacklistDelete
   */
  struct MeshBlacklistDeleteParam *mesh_blacklist_delete;
  struct MeshWanSpeedTestParam *mesh_wan_speed_test;
  /**
   * for ModeUpdate
   */
  struct MeshModeUpdateParam *mesh_mode_update;
  /**
   * AutoUpgradeSet
   */
  struct MeshAutoUpgradeSetParam *mesh_auto_upgrade_set;
  struct MeshDeviceGetParam *mesh_device_get;
  struct MeshDeviceTimeLimitGetParam *mesh_device_time_limit_get;
  struct MeshRsvdipDeleteParam *mesh_rsvdip_delete;
  struct VpnConfig *vpn_info_conf;
  struct ParamGetCertUrls *get_cert_urls;
  struct TimeLimit *add_time_limit_rule;
  struct TimeLimitDelParam *del_time_limit_rule;
  struct MeshRegionUpdateParam *mesh_region_update;
  struct MeshConfigUpdateParam *mesh_config_update;
  struct MeshConfigAdminUpdateParam *mesh_config_admin_update;
  struct MeshNodeGetResult *mesh_node_get;
  struct MeshNodeUpgradeParam *mesh_node_upgrade;
  struct MeshLedTimeLimitUpdateParam *mesh_led_time_limit_update;
  struct MeshConfigWanNetIpv6UpdateParam *mesh_config_wan_net_ipv6_update;
  struct NodeUpgradeParam *node_upgrade;
  struct MeshRsvdipUpdateParam *mesh_rsvdip_update;
  struct MeshNetworkRebootParam *mesh_network_reboot;
  struct MeshNodeUpdateParam *mesh_node_update;
  struct NodeUpdateParam *node_update;
  struct MeshUpnpEnabledUpdateParam *mesh_upnp_enabled_update;
  struct MeshConfigWanMacUpdateParam *mesh_config_wan_mac_update;
  struct RouterConfigFrozenUpdateParam *router_config_frozen_update;
  struct MeshNodeDeleteParam *mesh_node_delete;
  struct RouterPasswordCheckParam *router_password_check;
  struct MeshNetworkDiagnoseParam *mesh_network_diagnose;
  struct RouterTr069UpdateParam *router_tr069_update;
  struct FirmwareGetParam *firmware_get;
  struct RouterLoginParam *router_login;
  struct RequestGetParam *request_get;
  struct RouterIsLoginParam *router_is_login;
  struct MeshInfoGetParam *mesh_info_get;
  struct FactoryCmdExecuteParam *factory_cmd_execute;
} Param;

typedef struct CommandBody {
  char *id;
  enum Method method;
  char *session;
  struct Param param;
} CommandBody;

/**
 * 路由命令结构体。
 */
typedef struct RouterCommand {
  struct Meta meta;
  struct CommandBody body;
} RouterCommand;

/**
 * 用于处理基础的 status: bool 的接口
 */
typedef struct RouterCommandResponseResultStatusResult {
  bool status;
} RouterCommandResponseResultStatusResult;

typedef struct MeshWanSpeedTestResult {
  enum MeshWanSpeedTestResultStatus status;
  struct Speed speed;
  uint32_t latency;
  uint32_t loss_rate;
  uint32_t jitter;
} MeshWanSpeedTestResult;

typedef struct MeshWanSpeedTestReportResultSpeed {
  struct Speed speed;
  uint32_t latency;
  uint32_t loss_rate;
  uint32_t jitter;
} MeshWanSpeedTestReportResultSpeed;

/**
 * for noc
 */
typedef struct MeshWanSpeedTestReportResult {
  struct MeshWanSpeedTestReportResultSpeed speed;
} MeshWanSpeedTestReportResult;

typedef struct MeshModeGetResult {
  enum RouterMode mode;
  int32_t rssi;
  char *sn;
} MeshModeGetResult;

typedef struct MeshAutoUpgradeGetResult {
  bool enabled;
  /**
   * 以 Invalid 结尾
   */
  enum ScheduleWeekday **schedule;
  struct ScheduleTime time;
} MeshAutoUpgradeGetResult;

typedef struct VpnError {
  int32_t code;
  char *message;
} VpnError;

typedef struct MeshVpnInfoGetResult {
  struct VpnConfig config;
  /**
   * 建立连接后的时间戳,单位为ms
   */
  uint32_t connected_time;
  enum VpnConnectStatus status;
  struct NetInfo netinfo;
  struct VpnError error;
} MeshVpnInfoGetResult;

typedef struct MeshPortfwAddResult {
  bool status;
} MeshPortfwAddResult;

typedef struct MeshPortfwUpdateResult {
  bool status;
} MeshPortfwUpdateResult;

typedef struct MeshPortfwDeleteResult {
  bool status;
} MeshPortfwDeleteResult;

typedef struct ParentControl {
  enum PCMode mode;
  char **blacklist;
  char **whitelist;
} ParentControl;

typedef struct WifiBand {
  char *ssid;
  char *password;
  enum Encrypt encrypt;
  bool enabled;
  bool hidden;
  enum Mode mode;
  struct BandChannel channel;
} WifiBand;

typedef struct WifiBands {
  struct WifiBand band_2_4g;
  struct WifiBand band_5g;
} WifiBands;

typedef struct Wifi {
  struct WifiBands bands;
  /**
   * 双频合一，默认为true
   */
  bool smart_connect;
  bool compatibility_mode;
  enum ApiTxPower tx_power;
} Wifi;

typedef struct MeshDeviceTimeLimitGetResult {
  struct TimeLimit **time_limits;
} MeshDeviceTimeLimitGetResult;

typedef struct SupportedChannels {
  uint32_t **numbers;
} SupportedChannels;

typedef struct SupportedChannelsGetResp {
  struct SupportedChannels *g24;
  struct SupportedChannels *g5;
} SupportedChannelsGetResp;

typedef struct FirewallGetResp {
  struct FirewallRule rule;
} FirewallGetResp;

typedef struct IsRouterInitializedResp {
  bool is_initial;
} IsRouterInitializedResp;

typedef struct MeshDeviceCountGetResult {
  int32_t count;
} MeshDeviceCountGetResult;

typedef struct MeshMetaGetResult {
  struct Wifi *wifi;
  enum ApiTxPower tx_power;
  bool compatibility_mode;
} MeshMetaGetResult;

typedef struct AllSpeed {
  struct Speed peak;
  struct Speed average;
  struct Speed realtime;
} AllSpeed;

typedef struct MeshInfoWanStatsGetResult {
  struct AllSpeed speed;
  struct Traffic traffic;
  uint32_t bandwidth;
} MeshInfoWanStatsGetResult;

typedef struct MeshWanStatusGetResult {
  enum MeshWanStatus status;
} MeshWanStatusGetResult;

typedef struct MeshInfoWanNetGetResult {
  struct NetInfo *netinfo;
  enum WanMode typ;
  /**
   * type == pppoe
   */
  struct MeshInfoWanNetGetResultPPPoE *pppoe;
  /**
   * type == dhcp
   */
  struct MeshInfoWanNetGetResultDhcp *dhcp;
  struct MeshInfoWanNetGetResultStatic *static_;
  struct Vlan **vlan;
} MeshInfoWanNetGetResult;

typedef struct LANNetConfigDhcpServer {
  char *ip_start;
  char *ip_end;
  /**
   * seconds
   */
  int32_t lease;
  char *domain;
  struct NetInfo netinfo;
} LANNetConfigDhcpServer;

typedef struct LANNetConfigDhcpDisabled {
  struct NetInfo netinfo;
} LANNetConfigDhcpDisabled;

typedef struct LANNetConfig {
  enum LANNetType typ;
  struct LANNetConfigDhcpServer dhcp_server;
  struct LANNetConfigDhcpDisabled dhcp_disabled;
} LANNetConfig;

typedef struct LANNetGetRespResult {
  struct LANNetConfig config;
  struct NetInfo netinfo;
} LANNetGetRespResult;

typedef struct MeshInfoTimezoneGetResult {
  struct Timezone timezone;
} MeshInfoTimezoneGetResult;

typedef struct MeshRegionGetResult {
  uint32_t id;
  uint32_t ip_country_id;
} MeshRegionGetResult;

typedef struct LedTimeLimit {
  bool enabled;
  char *begin_time;
  char *end_time;
} LedTimeLimit;

typedef struct RouterFirmwareCheckResultFwVersion {
  struct RouterModel model;
  char *version;
} RouterFirmwareCheckResultFwVersion;

typedef struct RouterFirmwareCheckResult {
  struct RouterFirmwareCheckResultFwVersion fw_info;
  struct WebUIRouter **can_upgrade_nodes;
} RouterFirmwareCheckResult;

typedef struct MeshNodeNewInfoResultMacs {
  char *mac_24;
  char *mac_5;
} MeshNodeNewInfoResultMacs;

typedef struct MeshNodeNewInfoResult {
  char *sn;
  struct MeshNodeNewInfoResultMacs mac;
} MeshNodeNewInfoResult;

typedef struct MeshToolsExecuteResult {
  enum MeshToolsExecuteResultStatus status;
  char *output;
} MeshToolsExecuteResult;

typedef struct Ddns {
  bool enabled;
  enum DdnsService service;
  enum DdnsStatus status;
  char *domain;
  char *username;
  char *password;
} Ddns;

typedef struct MeshUpnpEnabledGetResult {
  bool status;
} MeshUpnpEnabledGetResult;

typedef struct MeshUpnpEnabledUpdateResult {
  bool status;
} MeshUpnpEnabledUpdateResult;

typedef struct MeshInfoWanMacGetResult {
  char *dft;
  char *current;
} MeshInfoWanMacGetResult;

typedef struct MeshConfigWanMacUpdateResult {
  bool status;
} MeshConfigWanMacUpdateResult;

typedef struct RouterWwaGetResult {
  bool enabled;
  int32_t port;
  char **allowed_ip;
} RouterWwaGetResult;

typedef struct RouterConfigFrozenGetResult {
  bool enabled;
  enum RouterConfigFrozenGetResultSupportedConfig **configs;
} RouterConfigFrozenGetResult;

typedef struct RouterConfigBackupCreateResult {
  bool status;
} RouterConfigBackupCreateResult;

typedef struct MeshSyslogEnabledGetResult {
  bool enabled;
} MeshSyslogEnabledGetResult;

typedef struct RouterPasswordCheckResult {
  char *id;
  char *ssid;
} RouterPasswordCheckResult;

typedef struct RouterNeighbor {
  char *sn;
  int32_t rssi;
} RouterNeighbor;

typedef struct RouterChannel {
  int32_t chan_5g;
  int32_t chan_24g;
  int32_t mesh;
} RouterChannel;

typedef struct RouterCmpVersion {
  char *current;
  char *latest;
} RouterCmpVersion;

typedef struct RouterMemory {
  int32_t total;
  int32_t used;
} RouterMemory;

typedef struct RouterPort {
  uint32_t id;
  bool is_wan;
  bool linked;
  uint64_t negotiation_rate_bps;
  /**
   * 是否全双工，目前写死 true 就行了
   */
  bool is_duplex;
} RouterPort;

typedef struct Router {
  char *sn;
  char *name;
  struct RouterMacs mac;
  bool is_gw;
  enum RouterStatus status;
  struct RouterNeighbor **neighbors;
  struct Station **stations;
  int32_t uptime_sec;
  char *ip;
  struct NetInfo lan;
  struct NetInfo wan;
  struct RouterChannel channel;
  char *version;
  struct RouterCmpVersion *cmp_version;
  struct RouterModel model;
  int32_t offline_time;
  float cpu;
  struct RouterMemory memory;
  struct RouterPort **ports;
} Router;

typedef struct AppMeshWan {
  struct AllSpeed speed;
  struct Traffic traffic;
  uint32_t bandwidth;
} AppMeshWan;

typedef struct AppMesh {
  char *id;
  char *ssid_2g;
  struct Router **nodes;
  enum RouterMode mode;
  uint32_t device_count;
  struct Timezone timezone;
  struct AppMeshWan wan;
} AppMesh;

typedef struct MeshNetworkDiagnoseResult {
  uint32_t latency;
  enum MeshWanStatus status;
} MeshNetworkDiagnoseResult;

typedef struct TrSettings {
  bool enabled;
  /**
   * router上报到远端的信息
   */
  struct TrSettingsRemote remote;
  /**
   * 远端获取router信息的地址
   */
  struct TrSettingsLocal local;
} TrSettings;

typedef struct RouterTr069GetResult {
  struct TrSettings settings;
} RouterTr069GetResult;

typedef struct FactoryCmdExecuteResult {
  char *output;
} FactoryCmdExecuteResult;

typedef struct MeshBandGetResult {
  bool g24;
  bool g5;
} MeshBandGetResult;

typedef struct DocsisCableModem {
  char *model;
  char *manufacturer;
  char *hw_version;
  char *sw_version;
  char *boot_version;
  uint32_t flash_size_m_bytes;
  char *serial_number;
  char *wan_mac_hr;
  char *emta_mac_hr;
  char *cm_mac_hr;
} DocsisCableModem;

typedef struct DocsisInternet {
  /**
   * Internet: Active/
   */
  bool connected;
  /**
   * Local time
   */
  uint32_t local_time_sec;
  /**
   * Uptime
   */
  uint32_t uptime_sec;
  /**
   * wan ip
   */
  char *wan_ip_v4;
  /**
   * wan mask
   */
  char *wan_mask_v4;
  /**
   * wan gateway
   */
  char *wan_gateway_v4;
  /**
   * wan ipv6 ip
   */
  char *wan_ip_v6;
  /**
   * wan ipv6 prefix
   */
  char *wan_prefix_v6;
  /**
   * wan ipv6 gateway
   */
  char *wan_gateway_v6;
  /**
   * primary dns ipv4
   */
  char *primary_dns_v4;
  /**
   * second dns ipv4
   */
  char *second_dns_v4;
  /**
   * primary dns ipv6
   */
  char *primary_dns_v6;
  /**
   * second dns ipv6
   */
  char *second_dns_v6;
  /**
   * wan link local addr ipv6
   */
  char *wan_link_local_addr_v6;
  bool dhcp_cli_v4;
  bool dhcp_cli_v6;
  uint32_t dhcp_lease_v4_expire_sec;
  uint32_t dhcp_lease_v6_expire_sec;
} DocsisInternet;

typedef struct DocsisInitProcedure {
  enum DocsisProcedureState hw_initialized;
  enum DocsisProcedureState acqure_downstream;
  enum DocsisProcedureState upstream_ranging;
  enum DocsisProcedureState dhcp_bound;
  enum DocsisProcedureState set_time_of_day;
  enum DocsisProcedureState config_file_download;
  enum DocsisProcedureState registration;
} DocsisInitProcedure;

typedef struct DocsisChannelBondingValue {
  uint32_t index;
  bool locked;
  uint32_t frequency_hz;
  uint32_t snr;
  uint32_t symbol_rate;
  char *modulation;
  uint32_t power_level_percent;
  char *channel_type;
} DocsisChannelBondingValue;

typedef struct DocsisCmStatus {
  struct DocsisCableModem cable_modem;
  struct DocsisInternet internet;
  struct DocsisInitProcedure init_procedure;
  struct DocsisChannelBondingValue downstream;
  struct DocsisChannelBondingValue upstream;
} DocsisCmStatus;

typedef struct DocsisMtaProvisionningStatus {
  bool initilized;
  char *line_1_status;
  char *line_2_status;
} DocsisMtaProvisionningStatus;

typedef struct DocsisCmPacketCableOptions {
  char *dhcp_primary;
  char *dhcp_secondary;
} DocsisCmPacketCableOptions;

typedef struct DocsisDhcpParam {
  char *mta_fqdn;
  char *mta_ip_v4;
  char *mta_ip_v6;
  char *mta_boot_file;
} DocsisDhcpParam;

typedef struct DocsisMtaIpTimeRemaining {
  uint32_t dhcp_lease_time_sec;
  uint32_t dhcp_rebind_time;
  uint32_t dhcp_renew_time;
} DocsisMtaIpTimeRemaining;

typedef struct DocsisDhcpOption {
  char *primary_dns_v4;
  char *second_dns_v4;
} DocsisDhcpOption;

typedef struct DocsisMtaPacketCableOptions {
  char *sub_option_3;
  char *sub_option_6;
  char *sub_option_7;
  char *sub_option_8;
} DocsisMtaPacketCableOptions;

typedef struct DocsisMtaStatus {
  struct DocsisMtaProvisionningStatus provision_status;
  struct DocsisCmPacketCableOptions cm_packet_cable_options;
  struct DocsisDhcpParam dhcp_param;
  struct DocsisMtaIpTimeRemaining ip_time_remaining;
  struct DocsisDhcpOption dhcp_option;
  struct DocsisMtaPacketCableOptions mta_packet_cable_options;
} DocsisMtaStatus;

typedef struct RouterCommandResponseResult {
  struct RouterCommandResponseResultStatusResult *common_result;
  struct MeshWanSpeedTestResult *mesh_wan_speed_test;
  struct MeshWanSpeedTestReportResult *mesh_wan_speed_test_report;
  struct MeshModeGetResult *mesh_mode_get;
  struct MeshAutoUpgradeGetResult *mesh_auto_upgrade_get;
  struct MeshVpnInfoGetResult *mesh_vpn_info_get;
  struct MeshPortfwAddResult *mesh_portfw_add;
  struct MeshPortfwUpdateResult *mesh_portfw_update;
  struct MeshPortfwDeleteResult *mesh_portfw_delete;
  struct Dmz *mesh_dmz_get;
  struct ParentControl *url_filter;
  struct SpeedLimit *speed_limit;
  struct Wifi *wifi_cfg;
  struct MeshDeviceTimeLimitGetResult *mesh_device_time_limit_get;
  struct SupportedChannelsGetResp *supported_channels_get;
  struct FirewallGetResp *firewall_get;
  struct IsRouterInitializedResp *is_initial;
  struct WebUIRouter *router_meta_get;
  struct MeshDeviceCountGetResult *mesh_device_count_get;
  struct MeshMetaGetResult *mesh_meta_get;
  struct MeshInfoWanStatsGetResult *mesh_info_wan_stats_get;
  struct MeshWanStatusGetResult *mesh_wan_status_get;
  struct MeshInfoWanNetGetResult *mesh_info_wan_net_get;
  struct LANNetGetRespResult *mesh_info_lan_net_get;
  struct MeshInfoTimezoneGetResult *mesh_info_timezone_get;
  struct MeshRegionGetResult *mesh_region_get;
  struct LedTimeLimit *mesh_led_time_limit_get;
  struct RouterFirmwareCheckResult *router_firmware_check;
  struct MeshNodeNewInfoResult *mesh_node_new_info;
  struct MeshInfoWanIpv6Info *mesh_info_wan_net_ipv6_get;
  struct MeshToolsExecuteResult *mesh_tools_execute;
  struct Ddns *ddns;
  struct FirewallRule *firewall;
  struct MeshUpnpEnabledGetResult *mesh_upnp_enabled_get;
  struct MeshUpnpEnabledUpdateResult *mesh_upnp_enabled_update;
  struct MeshInfoWanMacGetResult *mesh_info_wan_mac_get;
  struct MeshConfigWanMacUpdateResult *mesh_config_wan_mac_update;
  struct RouterWwaGetResult *router_wwa_get;
  struct RouterConfigFrozenGetResult *router_config_frozen_get;
  struct RouterConfigBackupCreateResult *router_config_backup_create;
  struct RouterConfigBackupCreateResult *router_config_backup_restore;
  struct MeshSyslogEnabledGetResult *mesh_syslog_enabled_get;
  struct RouterPasswordCheckResult *router_password_check;
  struct AppMesh *mesh_info_get;
  struct MeshNetworkDiagnoseResult *mesh_network_diagnose;
  struct RouterTr069GetResult *router_tr069_get;
  struct FactoryCmdExecuteResult *factory_cmd_execute;
  struct MeshBandGetResult *mesh_band_get;
  struct DocsisCmStatus *docsis_cm_status_get;
  struct DocsisMtaStatus *docsis_mta_status_get;
} RouterCommandResponseResult;

typedef struct MeshNodeUpgradabilityGetResultItemVersion {
  char *current;
  char *latest;
} MeshNodeUpgradabilityGetResultItemVersion;

typedef struct MeshNodeUpgradabilityGetItem {
  char *sn;
  struct RouterModel model;
  char *name;
  char *changelog;
  struct MeshNodeUpgradabilityGetResultItemVersion version;
} MeshNodeUpgradabilityGetItem;

typedef struct RouterLoginResult {
  enum SessionRole role;
  char *session;
  bool status;
} RouterLoginResult;

typedef struct MeshConfigWifiTimeLimitGetResult {
  char *id;
  char *time_begin;
  char *time_end;
  char *schedule;
  bool enabled;
  enum BandsType **bands;
} MeshConfigWifiTimeLimitGetResult;

typedef struct RequestGetResult {
  char *ip;
} RequestGetResult;

typedef struct Vpn {
  char *id;
  char *name;
  enum VpnProtocol protocol;
  char *server;
  char *username;
  char *password;
  struct VpnPptp pptp;
  struct VpnOpenvpn openvpn;
  struct WireguardCfg *wireguard;
} Vpn;

typedef struct GuestWifi {
  char *id;
  bool enabled;
  /**
   * integer, 开始连接的时间点，epoch ms UTC-0
   */
  uint32_t enabled_time;
  /**
   *integer, 访客网路开启时长(单位:s), -1 表示永久开启
   */
  int32_t duration;
  /**
   *integer, 剩余时长
   */
  uint32_t remaining_duration;
  /**
   * bool, 网络隔离(可选)
   */
  bool security;
  struct WifiBands bands;
  /**
   * bool, 双频合一
   */
  bool smart_connect;
} GuestWifi;

typedef struct DeviceAccessNode {
  char *name;
  char *sn;
} DeviceAccessNode;

typedef struct Device {
  char *mac;
  char *name;
  char *ip;
  uint64_t connected_time_ms;
  struct DeviceConnectedStatus connected_network;
  struct DeviceOnlineInfo online_info;
  struct SpeedLimit *speed_limit;
  struct TimeLimit **time_limit;
  struct ParentControl *parent_control;
  struct DeviceAccessNode access_node;
  uint64_t offline_time_ms;
} Device;

typedef struct PortFW {
  char *id;
  char *name;
  bool enabled;
  struct PortRulePair local;
  struct PortRulePair remote;
  enum PortFWProtocol protocol;
} PortFW;

typedef struct MacIpPair {
  char *id;
  char *name;
  char *ip;
  char *mac;
} MacIpPair;

typedef struct Region {
  int32_t region;
} Region;

typedef struct MeshNodeScanAvailableNodeMac {
  char *g_24;
  char *g_5;
} MeshNodeScanAvailableNodeMac;

typedef struct MeshNodeScanAvailableNode {
  char *sn;
  struct MeshNodeScanAvailableNodeMac mac;
} MeshNodeScanAvailableNode;

/**
 * 为了使路由器命令统一返回格式，采用此结构对返回值进行封装。
 */
typedef struct RouterCommandResponse {
  enum Method method;
  /**
   * 对于 router.login，提供此字段用于 set_cookie.
   */
  char *session;
  struct Response *error;
  struct RouterCommandResponseResult *result;
  struct MeshNodeUpgradabilityGetItem **mesh_node_upgradability_get;
  struct RouterLoginResult *router_login;
  struct MeshConfigWifiTimeLimitGetResult **mesh_config_wifi_time_limit_get;
  struct RequestGetResult *request_get;
  struct WebUIRouter **mesh_node_get;
  struct Vpn **mesh_vpn_get;
  struct GuestWifi **mesh_guestwifi_get;
  struct Device **mesh_device_get;
  struct PortFW **mesh_portfw_get;
  char *req_id;
  struct BLSta **mesh_blacklist_get;
  struct MacIpPair **mesh_rsvdip_get;
  struct Region **mesh_region_supported_get;
  struct MeshNodeScanAvailableNode **mesh_node_scan;
} RouterCommandResponse;

typedef struct MeshLocalNodeMacs {
  char *wlan_5g;
  char *wlan_2g;
  char *wan;
  char *lan;
  char *mesh_5g_ap;
  char *mesh_5g_sta;
  char *mesh_2g_ap;
  char *mesh_2g_sta;
} MeshLocalNodeMacs;

typedef struct MeshLocalNodeNeighbor {
  char *local_mac;
  char *remote_mac;
  /**
   * 信号强度。-100~0,越小代码信号越弱。有线时，使用 0 表示信号极好。
   */
  int32_t rssi;
  MeshBackhaulType bh_type;
} MeshLocalNodeNeighbor;

typedef struct MeshLocalNodeStation {
  char *mac;
  enum Band band;
  uint32_t onlinetime_sec;
  uint32_t rtspeedup;
  uint32_t rtspeeddown;
  uint32_t rx_bytes;
  uint32_t tx_bytes;
  int32_t negotiation_rate;
  int32_t rssi;
} MeshLocalNodeStation;

typedef struct MeshLocalNodeSysInfoMem {
  uint32_t total;
  uint32_t used;
} MeshLocalNodeSysInfoMem;

typedef struct MeshLocalNodeSysInfo {
  uint32_t cpu;
  struct MeshLocalNodeSysInfoMem mem;
} MeshLocalNodeSysInfo;

typedef struct MeshLocalNode {
  /**
   * 同步消息版本号，用于后续扩展
   */
  uint32_t msg_version;
  /**
   * 是否是 master 节点
   */
  bool is_master;
  char *ip;
  char *sn;
  char *name;
  int32_t rpc_port;
  enum MeshNodeState state;
  uint32_t progress;
  struct MeshLocalNodeMacs macs;
  struct MeshLocalNodeNeighbor **neighbors;
  struct MeshLocalNodeStation **stations;
  struct MeshLocalNodeSysInfo system_info;
  bool is_gw;
  char *version;
  uint64_t uptime_sec;
  /**
   * 由 master 填充
   */
  uint64_t last_seen_sec;
} MeshLocalNode;

typedef struct MeshLocalNodeTopology {
  struct MeshLocalNode **neighbors;
} MeshLocalNodeTopology;

/**
 * 一个map.
 * 注意：
 * 1. value 是指针，所以需要在外部分配内存.
 * 2. value 的所有权归此 map 所有，外部不能释放内存，否则会导致内存错误.
 * 3. value 被此 map 释放后，需要由外部进行释放。
 */
typedef void *Map;

typedef struct MapTuple {
  const char *key;
  const void *value;
} MapTuple;

typedef struct NetworkInfoOutputIpv4 {
  char *ip;
  uint32_t mask_index;
} NetworkInfoOutputIpv4;

typedef struct NetworkInfoOutputIpv4Route {
  char *target;
  uint32_t mask_index;
  char *nexthop;
} NetworkInfoOutputIpv4Route;

typedef struct NetworkInfoOutput {
  struct NetworkInfoOutputIpv4 **ipv4;
  struct NetworkInfoOutputIpv4Route **route;
  char **dns;
} NetworkInfoOutput;

typedef struct NetworkInfoOutputIpv6 {
  char *ip;
  uint32_t mask_index;
} NetworkInfoOutputIpv6;

typedef struct NetworkInfoOutputIpv6Route {
  char *target;
  uint32_t mask_index;
  char *nexthop;
} NetworkInfoOutputIpv6Route;

typedef struct NetworkIpv6InfoOutput {
  struct NetworkInfoOutputIpv6 **ipv6;
  struct NetworkInfoOutputIpv6Route **route;
  char **dns;
} NetworkIpv6InfoOutput;

typedef struct ApiServicePostArg {
  char *sn;
  char *mac;
} ApiServicePostArg;

/**
 *  * [{"id": "8ad0e2c49efa11eeab503203c5609312", "model": {"id": "08", "version": {"id": "1"}}, "model_version": "1", "version": "9.9.9", "version_code": 151587327, "status": "released", "released_time": 1703051113000, "pre_released_time": 1703051111000, "created_time": 1703050940000, "updated_time": 1703051113000, "changelog": "2.0.8-rc.6!!!!!!!!!!!!!!", "type": "upgrade", "url": "https://www.merckuwifi.net/download/firmware/M6a/M8R1/M6a-M8R1-v9.9.9.ma", "size": 13107902}]
 */
typedef struct FirmwareGetResponseItem {
  struct RouterModel model;
  char *version;
  char *changelog;
  char *url;
  uint32_t size;
  char **sns;
} FirmwareGetResponseItem;

typedef struct FirmwareGetResponse {
  struct FirmwareGetResponseItem **items;
} FirmwareGetResponse;

typedef struct NocInitDataAwsIotBasicIngest {
  bool enabled;
  char *topic_prefix;
} NocInitDataAwsIotBasicIngest;

typedef struct NocInitDataNoc {
  char *id;
  char *address;
  int32_t interval;
  struct NocInitDataAwsIotBasicIngest aws_iot_basic_ingest;
} NocInitDataNoc;

typedef struct StockRespError {
  uint32_t code;
  char *message;
} StockRespError;

typedef struct NocInitData {
  struct NocInitDataNoc *noc;
  struct StockRespError *error;
} NocInitData;

/**
 * AliasEntry is a struct that holds the mac and alias of a device
 */
typedef struct AliasEntry {
  char *mac;
  char *alias;
} AliasEntry;

/**
 * Holds all aliases in this router.
 */
typedef struct AliasBase {
  struct AliasEntry **entries;
} AliasBase;

/**
 * 暂时命名为AutoUpgradeCfgInner，避免与 vendor/all.h 中冲突
 */
typedef struct AutoUpgradeCfgInner {
  bool enabled;
  struct ScheduleTime time;
  enum ScheduleWeekday **schedule;
} AutoUpgradeCfgInner;

typedef struct DmzCfg {
  char *ip;
  bool enabled;
} DmzCfg;

typedef struct InitSSIDStrategy {
  enum InitSSIDStrategyType typ_;
  char *fixed_ssid;
  /**
   * sn 的前缀，比如 "Mercku-"
   */
  char *sn_custom_prefix;
  /**
   * 尾部长度，至少大于0，不然就和 fixed 一样了
   */
  uint32_t sn_custom_suffix_len;
  char *suffix;
} InitSSIDStrategy;

typedef struct InitWifiPsk {
  enum InitWifiPskEncryptType encrypt_type;
  enum InitWifiPskBuilder builder;
  /**
   * 固定初始密码
   */
  char *fixed;
  char *script;
} InitWifiPsk;

typedef struct MerckuGlobalCfg {
  char *router_host;
  char *customer_id;
  struct InitSSIDStrategy init_ssid_2g;
  struct InitSSIDStrategy init_ssid_5g;
  struct InitWifiPsk init_wifi_psk;
} MerckuGlobalCfg;

typedef struct ISO3166EntryFFI {
  char country[20];
  uint32_t country_code;
  char alpha2[4];
  char alpha3[4];
  uint32_t region_code;
  char region[20];
  char sub_region[40];
  uint32_t intermediate_region;
  uint32_t sub_region_code;
} ISO3166EntryFFI;

typedef struct MLedTimeLimitVO {
  bool enabled;
  struct ScheduleTime begin_time;
  struct ScheduleTime end_time;
} MLedTimeLimitVO;

typedef struct MeshSyncMsg {
  uint32_t msg_version;
  char *name;
  enum NodeWorkRole role;
  char *ip;
  char *br_lan_mac;
  char *wan_mac;
  char *sn;
  uint32_t rpc_port;
  char *version;
  struct MeshLocalNodeSysInfoMem system_info;
  bool is_gw;
  uint64_t uptime_sec;
} MeshSyncMsg;

typedef struct MeshSyncResp {
  enum Method method;
  ResponseErrorCode code;
  /**
   * 错误信息
   */
  char *msg;
} MeshSyncResp;

typedef struct PortFWList {
  struct PortFW **entries;
} PortFWList;

typedef struct MStaticIPRule {
  char *id;
  char *ip;
  char *name;
  char *mac;
} MStaticIPRule;

typedef struct MStaticIPRules {
  struct MStaticIPRule **rules;
} MStaticIPRules;

typedef struct VpnCfgEntry {
  uint32_t id;
  char *name;
  enum VpnProtocol proto;
  char *host;
  char *username;
  char *password;
  bool pptp_mppe;
  bool pptp_mppc;
  char *openvpn_config_file;
  struct WireguardCfg *wireguard;
} VpnCfgEntry;

typedef struct VpnList {
  struct VpnCfgEntry **vpns;
} VpnList;

typedef struct WwaCfg {
  bool enabled;
  uint32_t port;
  char **allow_ips;
} WwaCfg;

typedef struct RWanProfileCfgProfileVlan {
  uint32_t id;
} RWanProfileCfgProfileVlan;

typedef struct RWanProfileCfgProfilePppoe {
  char *username;
  char *password;
} RWanProfileCfgProfilePppoe;

typedef struct RWanProfileCfgProfile {
  uint32_t id;
  enum RWanProfileCfgProfileType typ;
  struct RWanProfileCfgProfileVlan vlan;
  struct RWanProfileCfgProfilePppoe pppoe;
} RWanProfileCfgProfile;

/**
 * {"enablded": true, "working_id": -1, "profiles":[{"id": 0, "type": "dhcp", "vlan": {"id": 911}}, {"id": 1, "type": "pppoe", "pppoe": {"username": "provisioning@mercku.com", "password": "provisioning"}, "vlan": {"id": 911}},{"id": 2, "type": "dhcp"}, {"id": 3, "type": "pppoe", "pppoe": {"username": "provisioning@mercku.com", "password": "provisioning"}}]}
 */
typedef struct RWanProfileCfg {
  bool enabled;
  /**
   * -1 表示未指定。其它值表示指定的profile id(必须 >= 0)
   */
  int32_t working_id;
  struct RWanProfileCfgProfile **profiles;
} RWanProfileCfg;

typedef struct MBlacklist {
  struct BLSta **entries;
} MBlacklist;

typedef struct Account {
  char *account;
  enum AccRole role;
  char *password;
} Account;

typedef struct MerckuAccounts {
  struct Account **accounts;
} MerckuAccounts;

typedef struct MtkDumpsTopologyInformationRadioBssInfoSta {
  char *mac;
  char *rssi_str;
  enum MtkDumpsTopologyInformationRadioBssInfoStaBhStaEnabled is_bh_sta;
  enum MtkDumpsTopologyInformationBhInfoConnectedType connect_type;
} MtkDumpsTopologyInformationRadioBssInfoSta;

typedef struct MtkDumpsTopologyInformationRadioBssInfo {
  char *bssid;
  char *ssid;
  struct MtkDumpsTopologyInformationRadioBssInfoSta **connected_stations;
} MtkDumpsTopologyInformationRadioBssInfo;

typedef struct MtkDumpsTopologyInformationRadio {
  char *channel;
  /**
   * "5"/"2"/"eth"?
   */
  char *wireless_mode;
  struct MtkDumpsTopologyInformationRadioBssInfo **bss_info;
} MtkDumpsTopologyInformationRadio;

typedef struct MtkDumpsTopologyInformationBhInfo {
  char *neighbor_mac;
  char *local_mac;
  enum MtkDumpsTopologyInformationBhInfoConnectedType connected_type;
  char *rssi_str;
} MtkDumpsTopologyInformationBhInfo;

typedef struct MtkDumpsTopologyInformationOtherClient {
  char *mac;
  enum MtkDumpsTopologyInformationBhInfoConnectedType connect_type;
} MtkDumpsTopologyInformationOtherClient;

typedef struct MtkDumpsTopologyInformation {
  /**
   * 格式为 01:23:45:67:89:ab
   */
  char *device_almac;
  enum MtkDumpsTopologyInformationMeshRole device_role;
  enum MtkDumpsTopologyInformationDistance distance_from_ctrl;
  /**
   * 2G/5G
   */
  struct MtkDumpsTopologyInformationRadio **radios;
  /**
   *
   */
  struct MtkDumpsTopologyInformationBhInfo **neighbors;
  struct MtkDumpsTopologyInformationOtherClient **other_clients;
} MtkDumpsTopologyInformation;

typedef struct MtkDumpsTopology {
  struct MtkDumpsTopologyInformation **topology;
} MtkDumpsTopology;

typedef struct Mtk7981DumpsTopologyInformationRadioBssInfoSta {
  char *mac;
  char *rssi_str;
  enum MtkDumpsTopologyInformationRadioBssInfoStaBhStaEnabled is_bh_sta;
  enum MtkDumpsTopologyInformationBhInfoConnectedType connect_type;
} Mtk7981DumpsTopologyInformationRadioBssInfoSta;

typedef struct Mtk7981DumpsTopologyInformationRadioBssInfo {
  char *bssid;
  char *ssid;
  struct Mtk7981DumpsTopologyInformationRadioBssInfoSta **connected_stations;
} Mtk7981DumpsTopologyInformationRadioBssInfo;

typedef struct Mtk7981DumpsTopologyInformationRadio {
  char *channel;
  /**
   * "5"/"2"/"eth"?
   */
  char *wireless_mode;
  struct Mtk7981DumpsTopologyInformationRadioBssInfo **bss_info;
} Mtk7981DumpsTopologyInformationRadio;

typedef struct Mtk7981DumpsTopologyInformationBhInfo {
  char *neighbor_mac;
  char *local_mac;
  enum MtkDumpsTopologyInformationBhInfoConnectedType connected_type;
  char *rssi_str;
} Mtk7981DumpsTopologyInformationBhInfo;

typedef struct Mtk7981DumpsTopologyInformationOtherClient {
  char *mac;
  enum MtkDumpsTopologyInformationBhInfoConnectedType connect_type;
} Mtk7981DumpsTopologyInformationOtherClient;

typedef struct Mtk7981DumpsTopologyInformation {
  /**
   * 格式为 01:23:45:67:89:ab
   */
  char *device_almac;
  enum MtkDumpsTopologyInformationMeshRole device_role;
  char *distance_from_ctrl;
  /**
   * 2G/5G
   */
  struct Mtk7981DumpsTopologyInformationRadio **radios;
  /**
   *
   */
  struct Mtk7981DumpsTopologyInformationBhInfo **neighbors;
  struct Mtk7981DumpsTopologyInformationOtherClient **other_clients;
} Mtk7981DumpsTopologyInformation;

typedef struct Mtk7981DumpsTopology {
  struct Mtk7981DumpsTopologyInformation **topology;
} Mtk7981DumpsTopology;

typedef char *(*CCallback)(const char*, void*);

typedef struct NocRouterCommandResponseMeta {
  /**
   * 固定为 1
   */
  int32_t api_version;
  /**
   * 以下发请求值为准
   */
  bool is_async;
} NocRouterCommandResponseMeta;

typedef struct NocRouterCommandResponseBodyResult {
  enum CmdStatus status;
  char *message;
  struct RouterCommandResponse *resp;
} NocRouterCommandResponseBodyResult;

typedef struct NocRouterCommandResponseParam {
  struct NocRouterCommandResponseBodyResult response;
} NocRouterCommandResponseParam;

typedef struct NocRouterCommandResponseBody {
  /**
   * sn/uuid/ip:port 格式
   */
  char *id;
  /**
   * 固定为 IGD.response
   */
  enum NocRouterCommandResponseBodyMethod method;
  struct NocRouterCommandResponseParam params;
} NocRouterCommandResponseBody;

typedef struct NocRouterCommandResponse {
  struct NocRouterCommandResponseMeta meta;
  struct NocRouterCommandResponseBody body;
} NocRouterCommandResponse;

typedef struct AppResponseMeta {
  char *req_id;
  char *response_topic;
  char *request_topic;
  char *server_send_time;
  char *router_send_time;
  char *router_recv_time;
  char *api_version;
} AppResponseMeta;

typedef struct AppResponseBodyError {
  uint32_t code;
  char *message;
} AppResponseBodyError;

typedef struct AppResponseBody {
  struct AppResponseBodyError *error;
  struct RouterCommandResponse *response;
} AppResponseBody;

typedef struct AppResponse {
  struct AppResponseMeta meta;
  struct AppResponseBody body;
} AppResponse;

/**
 * todo 这里是临时为 mesh.region.supported.get 提供的一个结构体，只是为了解决目前接口定义的问题，后面应该删除。
 */
typedef struct RouterCommandResponseSupportedRegions {
  enum Method method;
  struct Response *error;
  struct Region **result;
} RouterCommandResponseSupportedRegions;

/**
 * todo 这里是临时为 mesh.node.get 提供的一个结构体，只是为了解决目前接口定义的问题，后面应该删除。
 */
typedef struct RouterCommandResponseMeshNodeGet {
  enum Method method;
  struct Response *error;
  struct WebUIRouter **result;
} RouterCommandResponseMeshNodeGet;

/**
 * todo 这里是临时为 mesh.device.get 提供的一个结构体，只是为了解决目前接口定义的问题，后面应该删除。
 */
typedef struct RouterCommandResponseMeshDeviceGet {
  enum Method method;
  struct Response *error;
  struct Device **result;
} RouterCommandResponseMeshDeviceGet;

/**
 * todo 这里是临时为 mesh.guestwifi.get 提供的一个结构体，只是为了解决目前接口定义的问题，后面应该删除。
 */
typedef struct RouterCommandResponseMeshGuestwifiGet {
  enum Method method;
  struct Response *error;
  struct GuestWifi **result;
} RouterCommandResponseMeshGuestwifiGet;

typedef struct RouterCommandResponsePortfwGet {
  enum Method method;
  struct Response *error;
  struct PortFW **result;
} RouterCommandResponsePortfwGet;

typedef struct RouterCommandResponseVpnGet {
  enum Method method;
  struct Response *error;
  struct Vpn **result;
} RouterCommandResponseVpnGet;

typedef struct MeshConfigWifiSchedule {
  char *id;
  char *time_begin;
  char *time_end;
  char *schedule;
  bool enabled;
  enum BandsType **bands;
} MeshConfigWifiSchedule;

typedef struct RouterCommandResponseConfigWifiTimeLimitGetResult {
  enum Method method;
  struct Response *error;
  struct MeshConfigWifiSchedule **result;
} RouterCommandResponseConfigWifiTimeLimitGetResult;

typedef struct RouterCommandResponseMeshRsvdipGetResult {
  enum Method method;
  struct Response *error;
  struct MacIpPair **result;
} RouterCommandResponseMeshRsvdipGetResult;

typedef struct RouterCommandResponseMeshBlacklistGetResult {
  enum Method method;
  struct Response *error;
  struct BLSta **result;
} RouterCommandResponseMeshBlacklistGetResult;

typedef struct RouterCommandResponseMeshDeviceTimeLimitGetResult {
  enum Method method;
  struct Response *error;
  struct TimeLimit **result;
} RouterCommandResponseMeshDeviceTimeLimitGetResult;

typedef struct RespGetCertUrlsIot {
  char *host;
  uint32_t port;
} RespGetCertUrlsIot;

typedef struct RespGetCertUrls {
  char *root_ca;
  char *cert_perm;
  char *public_key;
  char *private_key;
  struct RespGetCertUrlsIot iot;
} RespGetCertUrls;

typedef struct HttpAPIRespResult {
  struct RespGetCertUrls *result_get_certs_urls;
} HttpAPIRespResult;

typedef struct HttpAPIResp {
  struct HttpAPIRespResult result;
} HttpAPIResp;

typedef struct IotKeysCertsUrlsResp {
  struct RespGetCertUrls *result;
} IotKeysCertsUrlsResp;

typedef struct MeshWan {
  struct AllSpeed speed;
  struct Traffic traffic;
  char *public_ip;
  enum WanMode mode;
  struct NetInfo netinfo;
} MeshWan;

typedef struct MeshLte {
  struct AllSpeed speed;
  struct Traffic traffic;
} MeshLte;

typedef struct Mesh {
  /**
   * 主路由器的 sn，用于标识主路由器
   */
  char *id;
  /**
   * 定制 ID，长度4位。
   */
  char *customer_id;
  struct Router **nodes;
  enum RouterMode mode;
  struct Wifi wifi;
  struct GuestWifi guest_wifi;
  int32_t region_id;
  struct MeshWan wan;
  /**
   * for 5g CPE only
   */
  struct MeshLte *lte;
  enum ReportMeshStatus status;
} Mesh;

typedef struct ReportBody {
  char *id;
  enum ReportMethod method;
  struct Mesh *params;
} ReportBody;

typedef struct Report {
  struct Meta meta;
  struct ReportBody body;
  int64_t timestamp;
} Report;

/**
 * 从 json 字符串(src)中解析出 Response 结构体。
 * 注意：
 * 1. 由于 Response 中有嵌套指针，所以需要调用者手动释放 Response 结构体；而不能简单地使用栈上的 Response 结构体。
 *
 * C 代码示例：
 * ```c
 * Response* resp = NULL;
 * FFIError err = response_from_json(json_str, &resp);
 * if (ffierror_is_ok(err)) {
 *    // do something
 *   response_free(resp);
 * } else {
 *  // do something
 * ffierror_free(err);
 * }
 * ```
 */
FFIError rust_response_from_json(const char *src,
                                 struct Response **dst);

/**
 * 释放 Response 结构体。
 * 注意：
 * 1. 由于 Response 中有嵌套指针，所以需要调用者手动释放 Response 结构体；而不能简单地使用栈上的 Response 结构体。
 */
void rust_response_free(struct Response *resp);

/**
 * 将 Response 结构体转换为 json 字符串。
 *
 * C 代码示例：
 * ```c
 * Response resp = {.code=0, .msg="hello"};
 * char* json_str = NULL;
 * FFIError err = response_to_json(&resp, &json_str);
 * if (ffierror_is_ok(err)) {
 *   // do something
 *   free(json_str);
 * } else {
 * // do something
 * ffierror_free(err);
 * }
 */
FFIError rust_response_to_json(const struct Response *resp, char **dst);

/**
 * 从 json 字符串(src)中解析出 RouterCommand 结构体。
 * 注意：
 * 1. 由于 RouterCommand 中有嵌套指针，所以需要调用者手动释放 RouterCommand 结构体；而不能简单地使用栈上的 RouterCommand 结构体。
 *
 * C 代码示例：
 * ```c
 * RouterCommand* cmd = NULL;
 * FFIError err = command_from_json(json_str, &cmd);
 * if (ffierror_is_ok(err)) {
 *   // do something
 *  router_command_free(cmd);
 * } else {
 * // do something
 * ffierror_free(err);
 * }
 * ```
 */
FFIError rust_router_command_from_json(const char *src,
                                       struct RouterCommand **dst);

FFIError rust_router_command_response_from_json(const char *src,
                                                struct RouterCommandResponse **dst);

int32_t rust_get_api_version(void);

/**
 * 初始化 RouterCommand 结构体的 meta 字段。
 */
FFIError rust_command_init_meta(struct RouterCommand *cmd, bool is_async);

/**
 * 释放 RouterCommand 结构体。
 * 注意：
 * 1. 由于 RouterCommand 中有嵌套指针，所以需要调用者手动释放 RouterCommand 结构体；而不能简单地使用栈上的 RouterCommand 结构体。
 * 2. 要保证传入的 RouterCommand 指针不是栈上的指针，否则会导致 double free。
 *
 */
void rust_router_command_free(struct RouterCommand *cmd);

struct RouterCommand *rust_router_command_new(enum Method method);

/**
 * 序列化 RouterCommand 结构体为 json 字符串。
 *
 * C 代码示例：
 * ```c
 * RouterCommand cmd = {
 *    .meta = {
 *       .api_version = 1,
 *      .is_async = 0,
 *  },
 * .body = {
 *   .id = "hello",
 * .param = {
 *  .empty = 0,
 * .resp = {
 *  .response = {
 *  .code = 0,
 * .msg = "hello",
 * }
 * }
 *
 */
FFIError rust_router_command_to_json(const struct RouterCommand *cmd, char **dst);

void rust_mesh_local_node_topology_free(struct MeshLocalNodeTopology *topo);

FFIError rust_mesh_local_node_topology_from_json(const char *src,
                                                 struct MeshLocalNodeTopology **dst);

FFIError rust_mesh_local_node_topology_to_json(const struct MeshLocalNodeTopology *topo,
                                               char **dst);

FFIError rust_local_mesh_node_from_json(const char *src, struct MeshLocalNode **dst);

void rust_local_mesh_node_free(struct MeshLocalNode *node);

FFIError rust_local_mesh_node_to_json(const struct MeshLocalNode *node, char **dst);

/**
 * method 枚举转换为字符串。
 * 注意：
 * 1. 返回的字符串需要调用者手动释放。
 */
char *rust_method_to_string(enum Method method);

/**
 * 初始化一个map.
 */
Map rust_map_new(void);

/**
 * 释放map. 返回当前还存在的 value 数组，由外部进行释放。
 * 注意：
 * 1. 返回的数组以 null 结尾。
 * 2. 如果原来已经没有元素了，返回 null。
 */
void **rust_map_free(Map map);

/**
 * 添加元素, 并返回原 value 指针。
 * 注意：
 * todo key 释放问题需要确定
 * 1. key 会被复制，并由 map 进行释放。
 * 2. 返回的原 value 由外部进行释放。
 * 3. 新插入的 value 在 map 释放前，不能进行释放，否则会导致内存错误。
 * 即，此处获取的 value 是引用关系，外部需要保证其生命周期。
 */
void *rust_map_insert(Map map, const char *key, void *value);

/**
 * 删除元素, 并返回原 value 指针。
 * 注意：
 * 1. 原 value 由外部进行释放。
 */
void *rust_map_remove(Map map, const char *key);

/**
 * 获取元素, 并返回 value 只读指针。
 * 注意：
 * 1. value 所有权归此 map 所有，外部不能释放内存，否则会导致内存错误。
 * 2. 此方法只返回只读指针，外部不能修改 value。
 * 3. 如果需要修改 value，需要调用 map_get_mut 方法。
 */
const void *rust_map_get(Map map, const char *key);

/**
 * 获取元素, 并返回 value 指针。
 * 注意：
 * 1. value 所有权归此 map 所有，外部不能释放内存，否则会导致内存错误。
 */
void *rust_map_get_mut(Map map, const char *key);

/**
 * 获取元素个数。
 */
int rust_map_count(Map map);

/**
 * 合并两个 map，将 src 中的元素合并到 dst 中。
 * 合并后，多余的 value 由调用方进行释放。
 * 注意：
 * 1. 返回值是以 NULL 结尾的 void* 指针，需要由调用方自己释放。
 *
 * 示例：
 * ```C
 * void** values = map_merge(dst, src);
 * for (int i = 0; values[i] != NULL; i++) {
 *    free(values[i]);
 * }
 * free(values);
 * ```
 */
void **rust_map_merge(Map dst, Map src);

/**
 * 遍历 map，返回一个以 NULL 结尾的 MapTuple 指针数组。
 * 注意：
 * 1. 返回的数组需要由调用方进行释放，但是数组中的元素*不能*进行释放。
 *
 * 示例:
 * ```C
 * MapTuple** tuples = map_iterate(map);
 * for (int i = 0; tuples[i] != NULL; i++) {
 *    MapTuple* tuple = tuples[i];
 *   printf("key: %s, value: %d\n", tuple->key, *(int*)tuple->value);
 * }
 * free(tuples);
 * ```
 */
struct MapTuple **rust_map_iterate(Map map);

bool rust_ffierror_is_ok(FFIError err);

void rust_ffierror_free(FFIError err);

FFIError rust_network_info_output_from_json(const char *src, struct NetworkInfoOutput **dst);

void rust_network_info_output_free(struct NetworkInfoOutput *resp);

FFIError rust_network_ipv6_info_output_from_json(const char *src,
                                                 struct NetworkIpv6InfoOutput **dst);

void rust_network_ipv6_info_output_free(struct NetworkIpv6InfoOutput *resp);

struct ApiServicePostArg *rust_api_service_post_arg_from_json(const char *json);

void rust_api_service_post_arg_free(struct ApiServicePostArg *arg);

char *rust_api_service_post_arg_to_json(struct ApiServicePostArg *arg);

FFIError rust_firmware_get_response_from_json(const char *json, struct FirmwareGetResponse **dst);

void rust_firmware_get_response_debug(const struct FirmwareGetResponse *obj);

void rust_firmware_get_response_free(struct FirmwareGetResponse *obj);

FFIError rust_do_post_json(const char *url,
                           const char *json,
                           uint32_t conn_timeout_sec,
                           char **resp);

FFIError rust_download_file(const char *url, const char *file, uint32_t connection_timeout_sec);

FFIError rust_noc_init_data_from_json(const char *json, struct NocInitData **dst);

void rust_noc_init_data_free(struct NocInitData *ptr);

struct AliasBase *rust_alias_base_new(void);

void rust_alias_base_free(struct AliasBase *base);

FFIError rust_alias_base_to_json(const struct AliasBase *base, char **json);

FFIError rust_alias_base_from_json(const char *json, struct AliasBase **dst);

void rust_auto_upgrade_cfg_free(struct AutoUpgradeCfgInner *ptr);

FFIError rust_auto_upgrade_cfg_from_json(const char *json, struct AutoUpgradeCfgInner **dst);

FFIError rust_auto_upgrade_cfg_to_json(const struct AutoUpgradeCfgInner *cfg, char **json);

void rust_dmz_cfg_free(struct DmzCfg *ptr);

FFIError rust_dmz_cfg_from_json(const char *json, struct DmzCfg **dst);

FFIError rust_dmz_cfg_to_json(const struct DmzCfg *cfg, char **json);

void rust_mercku_global_cfg_free(struct MerckuGlobalCfg *ptr);

FFIError rust_mercku_global_cfg_from_json(const char *json, struct MerckuGlobalCfg **dst);

FFIError rust_mercku_global_cfg_from_yaml(const char *yaml, struct MerckuGlobalCfg **dst);

void rust_mercku_global_cfg_debug(const struct MerckuGlobalCfg *ptr);

void rust_iso3166_entry_free(struct ISO3166EntryFFI *inst);

/**
 * Get ISO3166 entry by country code.
 *
 */
bool iso3166_get_by_code(uint32_t code, struct ISO3166EntryFFI *entry);

bool iso3166_alpha2_from_code(uint32_t code, char (*alpha2)[4]);

bool iso3166_get_by_alpha2(const char *alpha2, struct ISO3166EntryFFI *entry);

void rust_led_time_cfg_free(struct MLedTimeLimitVO *ptr);

FFIError rust_led_time_cfg_from_json(const char *json, struct MLedTimeLimitVO **dst);

FFIError rust_led_time_cfg_to_json(const struct MLedTimeLimitVO *cfg, char **json);

void rust_mesh_sync_msg_free(struct MeshSyncMsg *ptr);

FFIError rust_mesh_sync_msg_from_json(const char *src, struct MeshSyncMsg **dst);

FFIError rust_mesh_sync_msg_to_json(const struct MeshSyncMsg *msg, char **dst);

char *rust_mesh_sync_resp_to_json(const struct MeshSyncResp *resp);

void rust_mesh_sync_resp_free(struct MeshSyncResp *resp);

FFIError rust_mesh_sync_resp_from_json(const char *src, struct MeshSyncResp **dst);

struct RouterCommandResponse *rust_mesh_sync_resp_to_router_command_resp(struct MeshSyncResp *resp);

struct MeshSyncResp *rust_router_command_resp_to_mesh_sync_resp(struct RouterCommandResponse *resp);

struct PortFWList *rust_portfw_list_new(void);

void rust_portfw_list_free(struct PortFWList *vpn_list);

FFIError rust_portfw_list_to_json(const struct PortFWList *list, char **json);

FFIError rust_portfw_list_from_json(const char *json, struct PortFWList **dst);

void rust_staticip_rule_free(struct MStaticIPRule *ptr);

void rust_staticip_rules_free(struct MStaticIPRules *ptr);

FFIError rust_staticip_rules_from_json(const char *json, struct MStaticIPRules **dst);

FFIError rust_staticip_rules_to_json(const struct MStaticIPRules *staticip_rules, char **json);

void rust_vpn_cfg_entry_free(struct VpnCfgEntry *ptr);

struct VpnList *rust_vpn_list_new(void);

void rust_vpn_list_free(struct VpnList *vpn_list);

FFIError rust_vpn_list_to_json(const struct VpnList *vpn_list, char **json);

FFIError rust_vpn_list_from_json(const char *json, struct VpnList **dst);

void rust_wwa_cfg_free(struct WwaCfg *ptr);

FFIError rust_wwa_cfg_from_json(const char *json, struct WwaCfg **dst);

FFIError rust_wwa_cfg_to_json(const struct WwaCfg *cfg, char **json);

void rust_wan_profile_cfg_free(struct RWanProfileCfg *cfg);

FFIError rust_wan_profile_cfg_from_json(const char *json, struct RWanProfileCfg **dst);

FFIError rust_wan_profile_cfg_to_json(const struct RWanProfileCfg *cfg, char **dst);

struct MBlacklist *rust_black_list_new(void);

void rust_black_list_free(struct MBlacklist *black_list);

FFIError rust_black_list_to_json(const struct MBlacklist *list, char **json);

FFIError rust_black_list_from_json(const char *json, struct MBlacklist **dst);

void rust_mercku_accounts_free(struct MerckuAccounts *ptr);

FFIError rust_mercku_accounts_from_yaml(const char *yaml, struct MerckuAccounts **dst);

FFIError rust_mercku_accounts_to_yaml(const struct MerckuAccounts *inst, char **yaml);

void rust_mercku_accounts_debug(const struct MerckuAccounts *ptr);

const char *rust_noc_server(void);

const char *rust_api_server(void);

uint64_t rust_mesh_local_node_neighbor_size(void);

uint64_t rust_mesh_local_node_size(void);

void rust_mesh_local_node_free(struct MeshLocalNode *node);

FFIError rust_mesh_local_node_from_json(const char *src, struct MeshLocalNode **dst);

FFIError rust_mesh_local_node_to_json(const struct MeshLocalNode *node, char **dst);

void rust_mtk_dumps_topology_free(struct MtkDumpsTopology *topo);

FFIError rust_mtk_dumps_topology_from_json(const char *src, struct MtkDumpsTopology **dst);

FFIError rust_mtk_dumps_topology_to_json(const struct MtkDumpsTopology *topo, char **dst);

void rust_mtk7981_dumps_topology_free(struct Mtk7981DumpsTopology *topo);

FFIError rust_mtk7981_dumps_topology_from_json(const char *src, struct Mtk7981DumpsTopology **dst);

FFIError rust_mtk7981_dumps_topology_to_json(const struct Mtk7981DumpsTopology *topo, char **dst);

FFIError rust_udp_bind(uint32_t port, bool broadcast, uint64_t timeout_ms);

FFIError rust_udp_recv(uint32_t port, uint8_t *buf, uint32_t *len);

void rust_udp_release(uint32_t port);

FFIError rust_send_udp_quickly(const char *ip, uint32_t port, const uint8_t *buf, uintptr_t len);

/**
 * 執行udp call 并返回結果。注意：這個如果發送廣播包，可能會有返回多個的情況。
 * @param output_size 用來接收返回值的buffer大小。它是輸入輸出參數，表示輸入時buffer大小，返回時表示實際返回值大小。
 * @return 錯誤碼。0表示成功，1表示發送失敗，2表示讀取超時, 3 表示返回包有问题。100 表示 unknown
 */
int32_t rust_udp_call(const char *ip,
                      uint32_t port,
                      uint32_t timeout_ms,
                      const uint8_t *input,
                      uint32_t input_size,
                      uint8_t *output,
                      uint32_t *output_size);

void rust_udp_oncall(uint32_t port, uint64_t timeout_ms, CCallback callback, void *cb_args);

void rust_command_body_free(struct CommandBody *body);

FFIError rust_command_body_to_json(const struct CommandBody *body, char **json);

FFIError rust_command_body_from_json(const char *src, struct CommandBody **dst);

struct RouterCommandResponseResultStatusResult *rust_status_result_new(bool status);

FFIError rust_noc_router_command_response_to_json(const struct NocRouterCommandResponse *body,
                                                  char **json);

void rust_noc_router_command_response_free(struct NocRouterCommandResponse *resp);

struct NocRouterCommandResponse *rust_noc_router_command_response_new(const char *id,
                                                                      enum CmdStatus status);

/**
 * 创建一个 RouterCommandResponse 结构体。
 * 注意：
 * 1. error 是空指针.
 * 2. result 是提前分配了的。
 */
struct RouterCommandResponse *rust_router_command_response_new(enum Method method);

/**
 * 创建一个 RouterCommandResponse 结构体。
 * 注意：
 * 1. error 是空指针.
 * 2. result 是空指针。
 */
struct RouterCommandResponse *rust_router_command_response_new_empty(enum Method method);

/**
 * msg: 所有权归调用者所有，此函数内部会复制数据。
 */
struct RouterCommandResponse *rust_router_command_response_new_error(enum Method method,
                                                                     ResponseErrorCode code,
                                                                     const char *msg);

/**
 * 释放 RouterCommandResponse
 */
void rust_router_command_response_free(struct RouterCommandResponse *resp);

FFIError rust_router_command_response_to_json(const struct RouterCommandResponse *body,
                                              char **json);

const char *rust_dummy_report(void);

struct AppResponse *rust_app_response_new(void);

void rust_app_response_free(struct AppResponse *ptr);

FFIError rust_app_response_to_json(const struct AppResponse *inst, char **dst);

void rust_app_mesh_free(struct AppMesh *inst);

void rust_router_command_response_supported_regions_free(struct RouterCommandResponseSupportedRegions *resp);

FFIError rust_router_command_response_supported_regions_to_json(const struct RouterCommandResponseSupportedRegions *body,
                                                                char **json);

void rust_router_command_response_mesh_node_get_free(struct RouterCommandResponseMeshNodeGet *resp);

FFIError rust_router_command_response_mesh_node_get_to_json(const struct RouterCommandResponseMeshNodeGet *body,
                                                            char **json);

void rust_router_command_response_mesh_device_get_free(struct RouterCommandResponseMeshDeviceGet *resp);

FFIError rust_router_command_response_mesh_device_get_to_json(const struct RouterCommandResponseMeshDeviceGet *body,
                                                              char **json);

void rust_router_command_response_mesh_guestwifi_get_free(struct RouterCommandResponseMeshGuestwifiGet *resp);

FFIError rust_router_command_response_mesh_guestwifi_get_to_json(const struct RouterCommandResponseMeshGuestwifiGet *body,
                                                                 char **json);

void router_command_response_portfw_get_free(struct RouterCommandResponsePortfwGet *resp);

FFIError router_command_response_portfw_get_to_json(const struct RouterCommandResponsePortfwGet *body,
                                                    char **json);

void rust_router_command_response_vpn_get_free(struct RouterCommandResponseVpnGet *resp);

FFIError rust_router_command_response_vpn_get_to_json(const struct RouterCommandResponseVpnGet *body,
                                                      char **json);

void rust_router_command_response_mesh_config_wifi_time_limit_get_free(struct RouterCommandResponseConfigWifiTimeLimitGetResult *resp);

FFIError rust_router_command_response_mesh_config_wifi_time_limit_get_to_json(const struct RouterCommandResponseConfigWifiTimeLimitGetResult *body,
                                                                              char **json);

void rust_router_command_response_mesh_rsvdip_get_free(struct RouterCommandResponseMeshRsvdipGetResult *resp);

FFIError rust_router_command_response_mesh_rsvdip_get_to_json(const struct RouterCommandResponseMeshRsvdipGetResult *body,
                                                              char **json);

void rust_router_command_response_mesh_blacklist_get_free(struct RouterCommandResponseMeshBlacklistGetResult *resp);

FFIError rust_router_command_response_mesh_blacklist_get_to_json(const struct RouterCommandResponseMeshBlacklistGetResult *body,
                                                                 char **json);

void rust_router_command_response_mesh_device_time_limit_get_free(struct RouterCommandResponseMeshDeviceTimeLimitGetResult *resp);

FFIError rust_router_command_response_mesh_device_time_limit_get_to_json(const struct RouterCommandResponseMeshDeviceTimeLimitGetResult *body,
                                                                         char **json);

FFIError rust_http_api_resp_from_json(const char *json, struct HttpAPIResp **dst);

void rust_iot_keys_certs_urls_resp_free(struct IotKeysCertsUrlsResp *ptr);

FFIError rust_iot_keys_certs_urls_resp_from_json(const char *json,
                                                 struct IotKeysCertsUrlsResp **dst);

FFIError rust_resp_get_cert_urls_from_json(const char *json, struct RespGetCertUrls **dst);

void rust_resp_get_cert_urls_free(struct RespGetCertUrls *ptr);

void rust_portfw_free(struct PortFW *ptr);

void rust_router_model_free(struct RouterModel *ptr);

FFIError rust_router_model_to_json(const struct RouterModel *model, char **json);

void rust_mesh_free(struct Mesh *mesh);

void rust_report_free(struct Report *report);

void rust_report_debug(const struct Report *report);

struct Report *rust_report_new(void);

FFIError rust_report_to_json(const struct Report *report, char **json);

char *rust_schedule_time_to_string(const struct ScheduleTime *inst);

FFIError rust_schedule_time_from_string(const char *json, struct ScheduleTime *dst);

uint64_t rust_device_connected_status_size(void);

uint64_t rust_speed_size(void);

uint64_t rust_traffic_size(void);

uint64_t rust_band_size(void);

uint64_t rust_bool_size(void);

uint64_t rust_device_access_node_size(void);

uint64_t rust_device_online_info_size(void);

uint64_t rust_mesh_device_get_result_size(void);

uint64_t rust_device_size(void);

void rust_wireguard_cfg_free(struct WireguardCfg *ptr);

void v2_rust_command_body_free(struct CommandBody *body);

FFIError v2_rust_command_body_to_json(const struct CommandBody *body, char **json);

struct RouterCommandResponseResultStatusResult *v2_rust_status_result_new(bool status);

FFIError v2_rust_noc_router_command_response_to_json(const struct NocRouterCommandResponse *body,
                                                     char **json);

void v2_rust_noc_router_command_response_free(struct NocRouterCommandResponse *resp);

struct NocRouterCommandResponse *v2_rust_noc_router_command_response_new(const char *id,
                                                                         enum CmdStatus status);

/**
 * 创建一个 RouterCommandResponse 结构体。
 * 注意：
 * 1. error 是空指针.
 * 2. result 是提前分配了的。
 */
struct RouterCommandResponse *v2_rust_router_command_response_new(enum Method method);

/**
 * 创建一个 RouterCommandResponse 结构体。
 * 注意：
 * 1. error 是空指针.
 * 2. result 是空指针。
 */
struct RouterCommandResponse *v2_rust_router_command_response_new_empty(enum Method method);

/**
 * msg: 所有权归调用者所有，此函数内部会复制数据。
 */
struct RouterCommandResponse *v2_rust_router_command_response_new_error(enum Method method,
                                                                        ResponseErrorCode code,
                                                                        const char *msg);

/**
 * 释放 RouterCommandResponse
 */
void v2_rust_router_command_response_free(struct RouterCommandResponse *resp);

FFIError v2_rust_router_command_response_to_json(const struct RouterCommandResponse *body,
                                                 char **json);

const char *v2_rust_dummy_report(void);

void v2_rust_mesh_free(struct Mesh *mesh);

void v2_rust_report_free(struct Report *report);

void v2_rust_report_debug(const struct Report *inst);

struct Report *v2_rust_report_new(void);

FFIError v2_rust_report_to_json(const struct Report *report, char **json);

struct AppResponse *v2_rust_app_response_new(void);

void v2_rust_app_response_free(struct AppResponse *ptr);

void v2_rust_app_response_debug(const struct AppResponse *inst);

FFIError v2_rust_app_response_to_json(const struct AppResponse *inst, char **dst);

void v2_rust_app_mesh_free(struct AppMesh *inst);

FFIError v2_rust_http_api_resp_from_json(const char *json, struct HttpAPIResp **dst);

void v2_rust_iot_keys_certs_urls_resp_free(struct IotKeysCertsUrlsResp *ptr);

FFIError v2_rust_iot_keys_certs_urls_resp_from_json(const char *json,
                                                    struct IotKeysCertsUrlsResp **dst);

FFIError v2_rust_resp_get_cert_urls_from_json(const char *json, struct RespGetCertUrls **dst);

void v2_rust_resp_get_cert_urls_free(struct RespGetCertUrls *ptr);

void v2_rust_portfw_free(struct PortFW *ptr);

char *v2_rust_schedule_time_to_string(const struct ScheduleTime *inst);

FFIError v2_rust_schedule_time_from_string(const char *json, struct ScheduleTime *dst);

uintptr_t v2_rust_device_connected_status_size(void);

uintptr_t v2_rust_speed_size(void);

uintptr_t v2_rust_traffic_size(void);

uintptr_t v2_rust_band_size(void);

uintptr_t v2_rust_bool_size(void);

uintptr_t v2_rust_device_access_node_size(void);

uintptr_t v2_rust_device_online_info_size(void);

uintptr_t v2_rust_mesh_device_get_result_size(void);

uintptr_t v2_rust_device_size(void);

void v2_rust_wireguard_cfg_free(struct WireguardCfg *ptr);

#endif // __NOC_API_H__
