#ifndef __MERCKU_CORE_UTILS_BITS_H__
#define __MERCKU_CORE_UTILS_BITS_H__

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t BitsMap;

#define bits_map_is_set(map, pos) (((map) & (1ULL << (pos))) != false)
#define bits_map_set_bit(map, pos) ((map) |= (1ULL << (pos)))
#define bits_map_clear_bit(map, pos) ((map) &= ~(1ULL << (pos)))
#define bits_map_toggle_bit(map, pos) ((map) ^= (1ULL << (pos)))

#endif // __MERCKU_CORE_UTILS_BITS_H__