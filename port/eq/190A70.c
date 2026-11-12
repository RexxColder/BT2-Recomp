#include "common.h"

extern s32 D_003877BC;

/* 0x00190A70: 1 when the flag D_003877BC is set, arg0 is not NULL, its pointer at +0x38 is not NULL and the halfword
 * at +0x44 of that has bit 1 set; else 0. */
s32 func_00190A70(u8 *arg0) {
    u8 *p;

    if (D_003877BC == 0 || arg0 == NULL) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0x38);
    if (p == NULL) {
        return 0;
    }
    return (*(u16 *)(p + 0x44) & 2) != 0;
}
