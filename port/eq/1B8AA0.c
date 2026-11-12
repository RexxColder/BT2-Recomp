#include "common.h"

extern u8 *gEftPtcl3Mgr;

s32 func_001B8AA0(s32 arg0) {
    u8 *base;
    u8 *d;
    u8 *a3;
    u8 *ent;
    s32 a1;
    s32 a2;

    base = (u8 *)arg0;
    d = gEftPtcl3Mgr;
    a3 = NULL;
    a2 = 0;
    a1 = *(s32 *)(d + 4);
    for (;;) {
        ent = (u8 *)(*(s32 *)d + a1 * 0x130);
        if (*(s32 *)ent != 0) {
            a1 += 1;
            a2 += 1;
            a1 = (a1 >= 0x2BC) ? 0 : a1;
            if (a2 < 0x2BC) {
                continue;
            }
        } else {
            a3 = ent;
            *(s32 *)(a3 + 0x120) = 0;
            *(s32 *)(a3 + 0x124) = 0;
            *(s32 *)(d + 4) = a1 + 1;
            if (*(s32 *)(d + 4) >= 0x2BC) {
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
            *(s32 *)(a3 + 0x124) = *(s32 *)(base + 4);
            *(s32 *)(*(s32 *)(base + 4) + 0x120) = (s32)a3;
        }
        *(s32 *)(base + 4) = (s32)a3;
    }
    return (s32)a3;
}
