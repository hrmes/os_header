/**
 * @file iptables.h
 * @author your name (you@domain.com)
 * @brief iptables 的 C 语言入口。之所以不直接调用 iptables 命令，是因为 iptables 命令的输出格式不稳定，不适合解析。另外，iptables 本身并不存储规则，在openwrt和其它系统下，对规则的存储会有所不同（比如 openwrt 是使用 uci）。所以，这里使用了一个抽象的接口，以便于在不同的系统下进行适配。
 * @version 0.1
 * @date 2024-03-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __MERCKU_CORE_IPTABLES_H__
#define __MERCKU_CORE_IPTABLES_H__

#include <stdint.h>
#include <core/mercku_error.h>

typedef struct
{
    // if not given, it will be set to "filter"
    char table[40];
    char chain[40];
} IptableChain;

typedef enum
{
    // -A/--append
    ICAAppendRule = 0,
    // -D/--delete
    ICADeleteRule,
    // -I/--insert
    ICAInsertRule,
    // -R/--replace
    ICAReplaceRule,
    // -F/--flush, 清空链
    ICAFlushChain,
    // -N/--new, 创建链
    ICANewChain,
    // -X/--delete-chain, 删除链
    ICADeleteChain,
    // -P/--policy, 设置默认策略
    ICASetPolicy,
    // --rename-chain, 重命名链
    ICARenameChain,
} IptableCmdAction;

typedef struct
{
    /// @brief 0 means not-given.
    uint32_t start;
    /// @brief 0 means not-given.
    uint32_t end;
} IptablePortRange;

const char *iptable_port_range_to_string(const IptablePortRange *self, const char *delimiter);

/// @brief ACCEPT, REJECT, DROP, MARK, NOTRACK
typedef enum
{
    /// @brief DROP: Drop the packet. 
    IRTDrop = 0,
    /// @brief ACCEPT: Accept the packet.
    IRTAccept,
    /// @brief REJECT: Reject the packet with an error message.
    IRTReject,
    /// @brief MARK: Mark the packet.
    IRTMark,
    /// @brief NOTRACK: Do not track the packet.
    IRTNotrack,
} IptableRuleTarget;

const char *iptable_rule_target_itoa(IptableRuleTarget target);
IptableRuleTarget iptable_rule_target_atoi(const char *target);

/// @brief iptables rule family. ipv4, ipv6 or any
typedef enum
{
    IFAny = 0,
    IFIpv4,
    IFIpv6,
} IptableFamily;

const char *iptable_family_itoa(IptableFamily family);
IptableFamily iptable_family_atoi(const char *family);

/**
 * @brief for filter table.
 *
 */
typedef struct
{
    /// @brief Unique identifier. It will be used for rule deletion. In uci system, it will be the section name.
    char id[20];
    /// @brief rule name. optional.
    char name[40];
    /// @brief traffic source zone. * for all. optional. If omitted, the rule applies to output traffic.
    char src[40];
    /// @brief Match incoming traffic from the specified source IP address. optional.
    char src_ip[20];
    /// @brief Match incoming traffic from the specified source MAC address. optional.
    char src_mac[20];
    IptablePortRange src_port;
    /// @brief Match destination traffic from the specified source port or port range. optional.
    char dest[40];
    /// @brief Match destination traffic to the specified destination IP address. optional.
    char dest_ip[20];
    /// @brief Match destination traffic to the specified destination MAC address. optional.
    char dest_mac[20];
    IptablePortRange dest_port;
    /// @brief Match incoming traffic using the given protocol. Can be one (or several when using list syntax) of tcp, udp, udplite, icmp, esp, ah, sctp, or all or it can be a numeric value, representing one of these protocols or a different one. default is "udp tcp"
    char proto[40];
    /// @brief If specified, match traffic against the given firewall mark, e.g. 0xFF to match mark 255 or 0x0/0x1 to match any even mark value. The match can be inverted by prefixing the value with an exclamation mark, e.g. !0x10 to match all but mark #16. optional.
    uint32_t mark;
    /// @brief target. -j
    IptableRuleTarget target;
    /// @brief Zeroes out the bits given by mask and ORs value into the packet mark. If mask is omitted, 0xFFFFFFFF is assumed.
    uint32_t set_mark;
    /// @brief Zeroes out the bits given by mask and XORs value into the packet mark. If mask is omitted, 0xFFFFFFFF is assumed.
    uint32_t set_xmark;
    /// @brief specify rules based on specific physical or logical network interfaces.
    char device[20];
    IptableFamily family;
} IptableRule;

MError *iptable_rule_valdate(const IptableRule *rule);

typedef enum
{
    /// @brief DNAT: Destination NAT
    INTDnat = 0,
    /// @brief SNAT: Source NAT
    INTSnat,
} IptableNatTarget;

const char *iptable_nat_target_itoa(IptableNatTarget target);
IptableNatTarget iptable_nat_target_atoi(const char *target);

/**
 * @brief
 *
 */
typedef struct
{
    /// @brief Unique identifier. It will be used for rule deletion.
    char id[20];
    IptableNatTarget target;
    char name[40];
    /// @brief traffic source zone. It's required for DNAT. Commonly, it's "wan".
    char src[20];
    /// @brief Match incoming traffic from the specified source IP address.
    char src_ip[20];
    /// @brief For DNAT, match incoming traffic directed at the given destination IP address. For SNAT rewrite the source address to the given address. It's required for SNAT.
    char src_dip[20];
    char src_mac[40];
    IptablePortRange src_port;
    IptablePortRange src_dport;
    /// @brief Specifies the traffic destination zone. It's required for SNAT.
    char dest[20];
    /// @brief Match destination traffic to the specified destination IP address.
    char dest_ip[20];
    IptablePortRange dest_port;
    /// @brief If specified, match traffic against the given firewall mark, e.g. 0xFF to match mark 255 or 0x0/0x1 to match any even mark value. The match can be inverted by prefixing the value with an exclamation mark, e.g. !0x10 to match all but mark #16.
    uint32_t mark;

    /// @brief 	Match incoming traffic using the given protocol. Can be one (or several when using list syntax) of tcp, udp, udplite, icmp, esp, ah, sctp, or all or it can be a numeric value, representing one of these protocols or a different one.
    char proto[20];

    IptableFamily family;
    /// @brief If set to true, the source and destination addresses of the packet will be swapped.
    bool reflection;
} IptableNat;

MError *iptable_nat_valdate(const IptableNat *nat);

typedef struct {
    char id[20];
    char interface[20];
    char target[40];
} IPRoute;



#endif // __MERCKU_CORE_IPTABLES_H__