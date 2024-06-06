#ifndef __SN_H__
#define __SN_H__

#include <stdbool.h>
#include <stdint.h>

#include "mercku_error.h"

typedef char Product[2];
typedef char Country[2];

uint8_t product_2_int(const Product self);
bool product_eq(const Product *left, const Product *right);
bool country_eq(const Country *left, const Country *right);
bool product_is_valid(const Product *p);

#define SN_LEN 15

typedef union
{
    struct
    {
        Product product;
        Country country;
        char factory;
        // 生产年份
        char year[2];
        // 生产周
        char week[2];
        // 硬件版本。与 product 一起组成 ABJ
        char hw_version;
        // 生产序列号。
        char serial_number[5];
    } parsed __attribute__((packed));
    struct
    {
        char A;
        char B;
        char C;

        char D;
        char E;
        char F;

        char G;
        char H;
        char I;

        char J;
        char K;
        char L;

        char M;
        char N;
        char O;
    } bits __attribute__((packed));
    char str[SN_LEN + 1];
} SN;

const char *sn_to_string(const SN *self);
SN *sn_new_empty();
SN *sn_new_from_string(const char *s);
typedef char SnModelStr[4];
void sn_get_model(const SN *self, SnModelStr model);
typedef char SnHwVersionStr[2];
void sn_get_hw_version(const SN *self, SnHwVersionStr hw_version);
void sn_free(SN *self);
MError *sn_parse(SN *self, const char *s);

#endif // __SN_H__