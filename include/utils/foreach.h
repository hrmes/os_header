#ifndef __FOREACH_H__
#define __FOREACH_H__

#include <core/gcc.h>

#define iter_null_term_array(idx, array) \
    for (int idx = 0; array && array[idx] != NULL; idx++)

#define count_null_term_array(count, array)                 \
    for (count = 0; array && array[count] != NULL; count++) \
    {                                                       \
    }
#define foreach_null_iterm_array(array, expr) \
    for (int index = 0; array && array[index] != NULL; index++) {\
    typeof(array[0]) current = array[index];\
    {expr}\
    }

#define array_size(array) (sizeof(array) / sizeof(array[0]))




#define foreach_with_size(array, size, expr) for (int index = 0; index < size; index+=1) {\
    typeof(array[0]) current = array[index];\
    {expr}\
}

#define foreach(array, expr) foreach_with_size(array, array_size(array), expr)

#endif // __FOREACH_H__