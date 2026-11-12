#include "common.h"

void *memcpy(void *arg0, void *arg1, u32 arg2);
extern s32 D_00356E98 __attribute__((section(".data")));

s32 func_002FEF90(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 s2;
    s32 s4;
    s32 a1;
    s32 s1;
    s32 v1;
    s32 p1;
    s32 k;
    u8 *p;
    u8 *v0p;
    u8 *dst;
    s32 *d;

    s2 = 0;
    s4 = 0;
    a1 = 0;
    if ((s8)arg1[0] != 0) {
        for (;;) {
            p = arg1 + s2;
            v1 = *p;
            if (v1 == 0x5C) {
                v1 = 0x2F;
                *p = 0x2F;
            }
            if (v1 == 0xA || v1 == 0xD || v1 == 0) {
                p1 = (s8)p[1];
                if (p1 == 0xA || p1 == 0xD || p1 == 0) {
                    s2 += 1;
                    v0p = arg1 + s2 - 1;
                } else {
                    v0p = p - 1;
                }
                v1 = (s8)*v0p;
                if (v1 == 0xA || v1 == 0xD) {
                    *v0p = 0;
                }
                s1 = s2 - a1;
                k = arg3 * s4;
                dst = (u8 *)(arg0 + arg2 * 8 + k + s4);
                memcpy(dst, arg1 + a1, (u32)s1);
                if ((s8)dst[s1 - 1] != 0) {
                    dst[s1] = 0;
                }
                v1 = s2 + 1;
                s4 += 1;
                a1 = v1;
                if (s4 == arg2) {
                    break;
                }
                s2 = v1;
                if ((s8)arg1[s2] == 0) {
                    break;
                }
            } else {
                s2 += 1;
                if ((s8)arg1[s2] == 0) {
                    break;
                }
            }
        }
    }
    d = &D_00356E98;
    if (d[0] == 0) {
        d[3] = arg3;
        d[2] = arg2;
        d[0] = arg0;
        d[1] = s4;
    }
    return s4;
}
