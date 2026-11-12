#include "common.h"

extern u8 *gEftDisc;

s32 func_00191A60(s32 arg0) {
    u8 *base;
    u8 *d;
    u8 *a3;
    u8 *ent;
    s32 a1;
    s32 a2;

    base = (u8 *)arg0;
    d = gEftDisc;
    a3 = NULL;
    a2 = 0;
    a1 = *(s32 *)(d + 4);
    for (;;) {
        ent = (u8 *)(*(s32 *)d + a1 * 0x150);
        if (*(s32 *)ent != 0) {
            a1 += 1;
            a2 += 1;
            a1 = (a1 >= 0xC8) ? 0 : a1;
            if (a2 < 0xC8) {
                continue;
            }
        } else {
            a3 = ent;
            *(s32 *)(a3 + 0x140) = 0;
            *(s32 *)(a3 + 0x144) = 0;
            *(s32 *)(d + 4) = a1 + 1;
            if (*(s32 *)(d + 4) >= 0xC8) {
                *(s32 *)(d + 4) = 0;
            }
            *(s32 *)(d + 8) = *(s32 *)(d + 8) + 1;
        }
        break;
    }
    if (a3 != NULL) {
        if (*(s32 *)base == 0) {
            *(s32 *)base = (s32)a3;
        }
        if (*(s32 *)(base + 4) != 0) {
            *(s32 *)(a3 + 0x144) = *(s32 *)(base + 4);
            *(s32 *)(*(s32 *)(base + 4) + 0x140) = (s32)a3;
        }
        *(s32 *)(base + 4) = (s32)a3;
    }
    return (s32)a3;
}
