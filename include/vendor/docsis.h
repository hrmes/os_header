#ifndef __MERCKU_VENDOR_DOCSIS_H__
#define __MERCKU_VENDOR_DOCSIS_H__

#include <stdint.h>
#include <core/all.h>

typedef struct
{
    char model[40];
    char manufacturer[40];
    char hw_version[40];
    char sw_version[40];
    char boot_version[40];
    char product_type[40];
    uint32_t flash_size_m_bytes;
    char serial_number[40];
    MacHr wan_mac;
    MacHr emta_mac;
    MacHr cm_mac;
} CMSCableModem;

typedef enum
{
    CMSINotStarted = 0,
    // more states here
    CMSICompeleted = 100,
} CMSInitState;

/**
 *
 * Initialization Procedure

Initialize Hardware: Complete

Acquire Downstream Channel: NotStarted

Upstream Ranging: NotStarted

DHCP bound: NotStarted

Set Time-of-Day: NotStarted

Configuration File Download: NotStarted

Registration: NotStarted
*/
typedef struct
{
    CMSInitState hw_initialization;
    CMSInitState acquire_downstream_channel;
    CMSInitState upstream_ranging;
    CMSInitState dhcp_bound;
    CMSInitState set_time_of_day;
    CMSInitState config_file_download;
    CMSInitState registration;
} CMSInitProcedure;

typedef struct
{
    uint32_t index;
    bool locked;
    uint32_t frequency_hz;
    uint32_t symbol_rate;
    uint32_t snr;
    uint32_t power_level_percent;
    /// 640QAM
    char modulation[20];
    char channel_type[20];
} ChannelBondingValue;

typedef struct
{
    CMSCableModem cable_modem;
    CMSInitProcedure init_procedure;
    ChannelBondingValue downstream;
    ChannelBondingValue upstream;
} CMStatus;

typedef enum
{
    MPSNotInit = 0,
} MtaProvisionningState;
/**
 * MTA Provisionning Status
 */
typedef struct
{
    MtaProvisionningState state;
} MtaProvisionningStatus;

typedef struct
{
    MtaProvisionningStatus mta_provision_status;
    struct
    {
        /**
         * CM PacketCable Options
         * Sub-option 1 Service Provider's Primary DHCP: 0.0.0.0.0.0
         * Sub-option 1 Service Provider's Secondary DHCP：0.0.0.0.0
         */
        char primary_dhcp[40];
        char secondary_dhcp[40];
    } cm_packet_cable_option;
    struct
    {
        /**
         * MTA DHCP Parameters
         * MTA FQDN:
         * MTA IP Address: 0.0.0.0
         * MTA IP Gateway: 0.0.0.0
         * MTA Bootfile
         */
        IPv4 mta_ip;
        char mta_fqdn[256];
        IPv4 mta_gateway;
        char boot_file[256];
    } mta_dhcp_param;
    struct
    {
        /**
         * MTA IP Time Remaining
         * DHCP Lease Time: D:0 H:0 M:0 S:0
         * DHCP Rebind Time: D:0 H:0 M:0 S:0
         * DHCP Renew Time: D:0 H:0 M:0 S:0
         */
        uint64_t dhcp_lease_time_sec;
        uint64_t dhcp_rebind_time_sec;
        uint64_t dhcp_renew_time_sec;
    } mta_ip_time_remaining;
    struct
    {
        /**
         * MTA DHCP Option 6
         * Network Primary DNS: 0.0.0.0
         * Network Secondary DNS: 0.0.0.0
         */
        IPv4 primary_dns;
        IPv4 secondary_dns;
    } mta_dhcp_option_6;
    struct
    {
        /**
         * MTA PacketCable Options(Option 122)
         * Sub-option 3:
         * Sub-option 6:
         * Sub-option 7:0
         * Sub-option 8:10
         */
        uint32_t sub_option_3;
        uint32_t sub_option_6;
        uint32_t sub_option_7;
        uint32_t sub_option_8;
    } mta_packet_cable_option;
} MTAStatus;

MError *m_docsis_get_cm_status(CMStatus *status);
MError *m_docsis_get_mta_status(MTAStatus *status);

#endif // __MERCKU_VENDOR_DOCSIS_H__