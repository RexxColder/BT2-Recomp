#include "common.h"

s32 func_00127480(u8 *arg0, s32 arg1) {
    u8 *v1p;
    u8 *a3p;
    s32 F;
    s32 A0;
    s32 v0;
    s32 a2;

    a2 = 1;
    v1p = *(u8 **)(arg0 + 0x60);
    if (v1p == NULL) {
        return 0;
    }
    F = *(s32 *)(v1p + 4);
    if (*(s32 *)(arg0 + 0xC) == 0) {
        if (arg1 == 0) {
            A0 = *(s32 *)(arg0 + 0x50);
            if (!(A0 & 0x20)) {
                if (A0 & 0x40) {
                    a2 = 0;
                } else if (F & 4) {
                    a2 = 0;
                }
            }
            v0 = F & 0x40;
        } else {
            a2 = ((F & 9) == 0);
            v0 = F & 0x40;
        }
        if (v0 != 0) {
            a2 = 0;
        }
        return a2;
    }
    if (arg1 == 1) {
        A0 = *(s32 *)(arg0 + 0x50);
        if (A0 & 0x80) {
            return 0;
        }
        if (F & 0x4000) {
            return 1;
        }
        return ((F & 0x109) == 0) ? 1 : 0;
    }
    if (arg1 == 0) {
        A0 = *(s32 *)(arg0 + 0x50);
        if (A0 & 0x20) {
            return 1;
        }
        if (A0 & 0x40) {
            return 0;
        }
        a3p = *(u8 **)(*(u8 **)(arg0 + 0x64) + 0x20);
        if (*(s32 *)(a3p + 4) != 0) {
            return ((F & 0x104) == 0) ? 1 : 0;
        }
        return (*(s32 *)(a3p + 8) == 4) ? 1 : 0;
    }
    if (arg1 < 0) {
        return 1;
    }
    if (arg1 == 2) {
        return ((F & 0x10D) == 0) ? 1 : 0;
    }
    return 1;
}
