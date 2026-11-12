#include "common.h"

u8 *func_0028BAA8(s32 arg0);

u8 *func_002B24C8(u8 *arg0, u8 *arg1, s32 *arg2) {
    u8 sp[0x300];
    u8 *s0;
    u8 *t0;
    u8 *t5;
    u8 *t8;
    s32 a0v;
    s32 s1;
    s32 a1;
    s32 a2;
    s32 t1;
    s32 t3;
    s32 v1;
    s32 tmp;
    s32 k;

    a0v = *(s32 *)arg0;
    s1 = *(s32 *)(arg0 + 4);
    s0 = arg0 + 8;
    if (arg2 != NULL) {
        *arg2 = a0v;
    }
    t8 = arg1;
    if (arg1 == NULL) {
        t8 = func_0028BAA8(a0v);
    }
    t5 = t8;
    if (s1 == 0) {
        return t8;
    }
    t0 = s0;
    a2 = *t0;
    for (;;) {
        t0 += 1;
        for (k = 0; k < 0x100; k++) {
            sp[k] = (u8)k;
        }
        a1 = 0;
        for (;;) {
            tmp = a1 + a2;
            if (a2 >= 0x80) {
                a2 = 0;
                a1 = (s16)(tmp - 0x7F);
            }
            if (a1 != 0x100) {
                t1 = 0;
                do {
                    v1 = *t0;
                    t0 += 1;
                    sp[a1] = (u8)v1;
                    if (a1 != (v1 & 0xFF)) {
                        sp[0x100 + a1] = *t0;
                        t0 += 1;
                    }
                    t1 = (s16)(t1 + 1);
                    a1 = (s16)(a1 + 1);
                } while (a2 >= t1);
            }
            if (a1 == 0x100) {
                break;
            }
            a2 = *t0;
            t0 += 1;
        }
        v1 = *t0;
        t0 += 1;
        t3 = *t0;
        t0 += 1;
        t3 = (s16)((v1 << 8) + t3);
        t1 = 0;
        for (;;) {
            if (t1 != 0) {
                t1 = (s16)(t1 - 1);
                a1 = sp[0x200 + t1];
            } else {
                t3 = (s16)(t3 - 1);
                if (t3 == -1) {
                    break;
                }
                a1 = *t0;
                t0 += 1;
            }
            if (a1 == sp[a1]) {
                *t5 = (u8)a1;
                t5 += 1;
            } else {
                sp[0x200 + t1] = sp[0x100 + a1];
                t1 = (s16)(t1 + 1);
                sp[0x200 + t1] = sp[a1];
                t1 = (s16)(t1 + 1);
            }
        }
        if ((s32)(t0 - s0) == s1) {
            break;
        }
        a2 = *t0;
    }
    return t8;
}
