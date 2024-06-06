#ifndef __MERCKU_GCC_H__
#define __MERCKU_GCC_H__

#define __GCC_INLINE__ inline __attribute__((always_inline))
#define stringify(x) #x

#define EXPORT_API __attribute__((visibility("default")))

#include <stdint.h>
#include <stdbool.h>
typedef double float64_t;
typedef float float32_t;


#define IN 
#define OUT
#define IN_OUT

#endif // __MERCKU_GCC_H__