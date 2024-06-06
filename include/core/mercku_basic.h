#ifndef __MERCKU_BASIC__
#define __MERCKU_BASIC__

#include <stdint.h>

#include "mercku_error.h"

typedef struct
{
    // 主版本号。设置为长度为2的数组是为了避免大小端问题。
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
    uint32_t rc;
} SemVer;

#define SEMVER_EMPTY \
    (SemVer) { 0, 0, 0, 0 }

/// 返回当前 OS 版本号。
const SemVer *current_merckuos_version();

MError *semver_from_parse(SemVer *self, const char *s);
const char *semver_to_string(const SemVer *self);
/// @brief 比较两个版本号。
/// @return 0: 相等; 1: left > right; -1: left < right
int semver_compare(const SemVer *left, const SemVer *right);

#endif // __MERCKU_BASIC__