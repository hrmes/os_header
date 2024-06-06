#ifndef __BASE_LIBS_MACADDR_H__
#define __BASE_LIBS_MACADDR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <core/mercku_error.h>

#include <net/ethernet.h>
#include <net/if_arp.h>

#define FMT_MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define FMT_MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"

/*
 * Compact form for string representation of MAC address
 * To be used, e.g., for constructing dbus paths for P2P Devices
 */
#define FMT_MACSTR_COMPACT "%02x%02x%02x%02x%02x%02x"

#define FMT_MACSTR_DOT "%02x%02x.%02x%02x.%02x%02x"
#define FMT_MACSTR_LINE "%02x%02x-%02x%02x-%02x%02x"

enum {
    MACADDR_FORMAT_NORMAL = 0, // colon-delimited format, "00:11:22:33:44:55"
    MACADDR_FORMAT_COMPACT,    // no colon-delimited format, "001122334455"
    MACADDR_FORMAT_DOT,        // dot-delimited format, "0011.2233.4455"
    MACADDR_FORMAT_LINE,       // line-delimited format, "0011-2233-4455"
};

#define MACADDR_FORMAT_DEFAULT MACADDR_FORMAT_NORMAL

/**
 * is_zero_macaddr - Determine if give Ethernet address is all zeros.
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Return true if the address is all zeroes.
 */
int is_zero_macaddr(const uint8_t *addr);

/**
 * is_multicast_macaddr - Determine if the Ethernet address is a multicast.
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Return true if the address is a multicast address.
 * By definition the broadcast address is also a multicast address.
 */
int is_multicast_macaddr(const uint8_t *addr);

/*
 * is_broadcast_macaddr - Determine if the Ethernet address is broadcast
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Return true if the address is the broadcast address.
 */
int is_broadcast_macaddr(const uint8_t *addr);

/*
 * is_valid_macaddr - Determine if the given Ethernet address is valid
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Check that the Ethernet address (MAC) is not 00:00:00:00:00:00, is not
 * a multicast address, and is not FF:FF:FF:FF:FF:FF.
 *
 * Return true if the address is valid.
 */
int is_valid_macaddr(const uint8_t *addr);

/**
 * macaddr_aton - Convert ASCII string to MAC address (colon-delimited format)
 * @txt: MAC address as a string (e.g., "00:11:22:33:44:55")
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * Returns: 0 on success, -1 on failure (e.g., string not a MAC address)
 */
int macaddr_aton(const char *txt, uint8_t *addr);

/**
 * macaddr_masked_aton - Convert ASCII string with optional mask to MAC address (colon-delimited format)
 * @txt: MAC address with optional mask as a string (e.g., "00:11:22:33:44:55/ff:ff:ff:ff:00:00")
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * @mask: Buffer for the MAC address mask (ETH_ALEN = 6 bytes)
 * @maskable: Flag to indicate whether a mask is allowed
 * Returns: 0 on success, -1 on failure (e.g., string not a MAC address)
 */
int macaddr_masked_aton(const char *txt, uint8_t *addr, uint8_t *mask, uint8_t maskable);

/**
 * macaddr_compact_aton - Convert ASCII string to MAC address (no colon delimitors format)
 * @txt: MAC address as a string (e.g., "001122334455")
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * Returns: 0 on success, -1 on failure (e.g., string not a MAC address)
 */
int macaddr_compact_aton(const char *txt, uint8_t *addr);

/**
 * macaddr_aton2 - Convert ASCII string to MAC address (in any known format)
 * @txt: MAC address as a string (e.g., 00:11:22:33:44:55 or 0011.2233.4455)
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * Returns: Characters used (> 0) on success, -1 on failure
 */
int macaddr_aton_any(const char *txt, uint8_t *addr);

int macaddr_mask_txt(char *buf, size_t len, const uint8_t *addr, const uint8_t *mask);

MError *random_macaddr(uint8_t *addr);

MError *random_macaddr_keep_oui(uint8_t *addr);

int upper_macaddr(uint8_t *addr, int32_t upper);
int upper_macaddr_str(const char *src, char *dst, int32_t upper);

bool is_valid_macstr(const char *macaddr);

/**
 * macaddr_ntoa_any - Convert MAC address to ASCII string (in any known format)
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * @txt: MAC address as a string (e.g., 00:11:22:33:44:55 or 0011.2233.4455)
 * @type: MAC address type enum
 * @caps_lock: true for upper string, false for lower string
 * Returns: Characters pointer of txt on success, NULL on failure
 */
char *macaddr_ntoa_any(const uint8_t *addr, char *txt, uint32_t type, bool caps_lock);

/**
 * macaddr_ntoa - Convert MAC address to ASCII string (in any known format)
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * @txt: MAC address as a string (AA:BB:CC:DD:EE:FF)
 * Returns: Characters pointer of txt on success, NULL on failure
 */
char *macaddr_ntoa(const uint8_t *addr, char *txt);

/**
 * macaddr_ntoa - Convert MAC address to ASCII string (in any known format)
 * @addr: Buffer for the MAC address (ETH_ALEN = 6 bytes)
 * @txt: MAC address as a string (AABBCCDDEEFF)
 * Returns: Characters pointer of txt on success, NULL on failure
 */
char *macaddr_ntoa_compact(const uint8_t *addr, char *txt);

/**
 * macaddr_format_any - Convert MAC address string format
 * @dst: Buffer for the MAC address string formated
 * @src: MAC address as a string (e.g., 00:11:22:33:44:55 or 0011.2233.4455)
 * @type: MAC address type enum
 * @caps_lock: true for upper string, false for lower string
 * Returns: Characters pointer of txt on success, NULL on failure
 */
char *macaddr_format_any(char *dst, char *src, uint32_t type, bool caps_lock);

/**
 * macaddr_format - Convert MAC address string format
 * @dst: Buffer for the MAC address string formated ("AA:BB:CC:DD:EE:FF")
 * @src: MAC address as a string (e.g., 001122334455 or 0011.2233.4455)
 * @type: MAC address type enum
 * @caps_lock: true for upper string, false for lower string
 * Returns: Characters pointer of txt on success, NULL on failure
 */
char *macaddr_format(char *dst, char *src);

/**
 * macaddr_strcmp - compare two MAC address string
 */
int32_t macaddr_strcmp(char *dst, char *src);

int macaddr_type_get(const char *macaddr, uint32_t *type);

#endif