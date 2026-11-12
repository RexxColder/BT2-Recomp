#include "common.h"

void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
s32 func_00126560(void);
extern u8 *gEftTechEvt;

/* 0x001742B0: block B = *(arg0+0x38); memset(B, 0, 0x1C); B[0..0xF] = arg1[0..0xF]; B[0x18] = 0. When
 * func_00126560() != 0, or the word +4 of the table *(arg1->+0x20) is 0, B[0x18] = 1 for every halfword of the table
 * at +0x3E (six entries) that is not -1. Then the word at gEftTechEvt+4 + (*arg1 << 4) + 4 is cleared; returns
 * gEftTechEvt (the value the asm leaves in v0). */
u8 *func_001742B0(u8 *arg0, u8 *arg1) {
    u8 *b = *(u8 **)(arg0 + 0x38);
    u8 *s3 = *(u8 **)arg1;
    u8 *s2 = *(u8 **)(s3 + 0x20);
    s32 k;

    memset(b, 0, 0x1C);
    memcpy(b, arg1, 16);
    b[0x18] = 0;
    if (func_00126560() != 0 || *(s32 *)(s2 + 0x4) == 0) {
        for (k = 0; k < 6; k++) {
            if (*(s16 *)(s2 + 0x3E + k * 2) != -1) {
                b[0x18] = 1;
            }
        }
    }
    *(s32 *)(*(u8 **)(gEftTechEvt + 0x4) + (*(s32 *)s3 << 4) + 0x4) = 0;
    return gEftTechEvt;
}
