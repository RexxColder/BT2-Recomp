#include "common.h"

extern u8 *gEftPtcl4Mgr;

s32 func_001BCC38(s32 arg0) {
    u8 *base;
    u8 *d;
    u8 *a2;
    u8 *ent;
    s32 a1;
    s32 a3;

    base = (u8 *)arg0;
    d = gEftPtcl4Mgr;
    a2 = NULL;
    a3 = 0;
    a1 = *(s32 *)(d + 4);
    for (;;) {
        ent = (u8 *)(*(s32 *)d + (a1 << 8));
        if (*(s32 *)ent != 0) {
            a1 += 1;
            a3 += 1;
            a1 = (a1 >= 0xC8) ? 0 : a1;
            if (a3 < 0xC8) {
                continue;
            }
        } else {
            a2 = ent;
            *(s32 *)(a2 + 0xE0) = 0;
            *(s32 *)(a2 + 0xE4) = 0;
            *(s32 *)(a2 + 0xE8) = 0;
            *(s32 *)(a2 + 0xEC) = 0;
            *(s32 *)(a2 + 0xF0) = 0;
            *(s32 *)(a2 + 0xF4) = 0;
            *(s32 *)(d + 4) = a1 + 1;
            if (*(s32 *)(d + 4) >= 0xC8) {
                *(s32 *)(d + 4) = 0;
            }
            *(s32 *)(d + 8) = *(s32 *)(d + 8) + 1;
        }
        break;
    }
    if (a2 != NULL) {
        if (*(s32 *)base == 0) {
            *(s32 *)base = (s32)a2;
        }
        if (*(s32 *)(base + 4) != 0) {
            *(s32 *)(a2 + 0xE4) = *(s32 *)(base + 4);
            *(s32 *)(*(s32 *)(base + 4) + 0xE0) = (s32)a2;
        }
        *(s32 *)(base + 4) = (s32)a2;
    }
    return (s32)a2;
}
