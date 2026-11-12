#include "common.h"

s32 *func_00202DA0(s32 arg0, s32 arg1);

s32 func_00202EA0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 s1;
    s32 a0v;
    u8 *v1;
    u8 *a1p;

    s1 = -1;
    if (*(s32 *)(arg0 + 0x1184) < 5) {
        a0v = 0;
        if (*(s32 *)(arg0 + 0x1410) < 0) {
            s1 = 0;
        } else {
            a0v = 1;
            while (a0v < 5 && *(s32 *)(arg0 + 0x1410 + a0v * 4) >= 0) {
                a0v += 1;
            }
            if (a0v < 5) {
                s1 = a0v;
            }
        }
        a0v = 0;
        v1 = arg0 + 0x1198;
        a1p = arg0 + 0x1190;
        if (s1 < 0) {
            return -1;
        }
        for (;;) {
            if (*v1 == 0) {
                break;
            }
            v1 += 0x80;
            a0v += 1;
            a1p += 0x80;
            if (a0v >= 5) {
                return -1;
            }
        }
        *(a1p + 8) = 1;
        *(s32 *)(arg0 + 0x1410 + s1 * 4) = a0v;
        *(s32 *)(arg0 + 0x1184) = *(s32 *)(arg0 + 0x1184) + 1;
        *func_00202DA0((s32)arg0, s1) = arg1;
        *(s32 *)((u8 *)func_00202DA0((s32)arg0, s1) + 4) = arg2;
        return s1;
    }
    return -1;
}
