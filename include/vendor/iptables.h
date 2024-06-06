#ifndef __MERCKU_VENDOR_IP6TABLES_H__
#define __MERCKU_VENDOR_IP6TABLES_H__

#include <utils/iptables.h>
#include <core/mercku_error.h>

/**
 * @brief 新增或者修改一个规则。
 *
 * @param rule
 * @return MError*
 */
MError *m_firewall_set_rule(const IptableRule *rule);
MError *m_firewall_del_rule(const char *id);
MError *m_firewall_apply();

MError *m_firewall_set_nat(const IptableNat *rule);
MError *m_firewall_del_nat(const char *id);

MError *m_iproute_set(const IPRoute *route);
MError *m_iproute_del(const char *id);

#endif // __MERCKU_VENDOR_IP6TABLES_H__