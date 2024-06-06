#ifndef __MERCKU_INTERNAL_CORE_ALGO_H__
#define __MERCKU_INTERNAL_CORE_ALGO_H__

#include <core/gcc.h>

// 为了避免溢出，使用 Kahan求和算法计算平均值的函数
float64_t kahan_sum(const uint64_t *arr, int n);

#endif // __MERCKU_INTERNAL_CORE_ALGO_H__