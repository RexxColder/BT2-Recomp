#include "common.h"

extern u8 *D_003876A4;
extern u8 *D_0042A588 __attribute__((section(".data")));

/* 0x003FB830: level query on P = D_003876A4 and Q = D_0042A588, R = Q->0x260 (120-byte entries, entry index P->0x64).
 * Case 0 (P->0x40 & 0x8000 gives 0): with T = Q->0x124, entry words +0, +4, +8, +C vs T give 5, 4, 3, 2; else
 * (E+0x10 >= T). Case 1: T = Q->0x128, words +2C, +28, +24, +20 give 0, 1, 2, 3; else (E+0x1C < T) ? 5 : 4.
 * Case 2: T = Q->0x12C, base +0x30, as case 0 with final +0x40. Case 3: T = Q->0x130, base +0x48, as case 0 with final
 * +0x58. Case 4: T = 24 - (Q[0x13C] + Q[0x140] + Q[0x144] + Q[0x148]) (each step t = t - w + 6), base +0x60, as case 0
 * with final +0x70. Other arg: 0. */
s32 func_003FB830(s32 arg0) {
    u8 *p;
    u8 *q;
    u8 *e;
    s32 t;
    s32 k;
    s32 thr;

    if ((u32)arg0 >= 5) {
        return 0;
    }
    switch (arg0) {
    case 0:
        p = D_003876A4;
        if (*(s32 *)(p + 0x40) & 0x8000) {
            return 0;
        }
        q = D_0042A588;
        thr = *(s32 *)(q + 0x124);
        e = *(u8 **)(q + 0x260) + 120 * *(s32 *)(p + 0x64);
        if (*(s32 *)(e + 0x0) >= thr) return 5;
        if (*(s32 *)(e + 0x4) >= thr) return 4;
        if (*(s32 *)(e + 0x8) >= thr) return 3;
        if (*(s32 *)(e + 0xC) >= thr) return 2;
        return (*(s32 *)(e + 0x10) >= thr) ? 1 : 0;
    case 1:
        p = D_003876A4;
        q = D_0042A588;
        thr = *(s32 *)(q + 0x128);
        e = *(u8 **)(q + 0x260) + 120 * *(s32 *)(p + 0x64);
        if (*(s32 *)(e + 0x2C) >= thr) return 0;
        if (*(s32 *)(e + 0x28) >= thr) return 1;
        if (*(s32 *)(e + 0x24) >= thr) return 2;
        if (*(s32 *)(e + 0x20) >= thr) return 3;
        return (*(s32 *)(e + 0x1C) < thr) ? 5 : 4;
    case 2:
        p = D_003876A4;
        q = D_0042A588;
        thr = *(s32 *)(q + 0x12C);
        e = *(u8 **)(q + 0x260) + 120 * *(s32 *)(p + 0x64);
        if (*(s32 *)(e + 0x30) >= thr) return 5;
        if (*(s32 *)(e + 0x34) >= thr) return 4;
        if (*(s32 *)(e + 0x38) >= thr) return 3;
        if (*(s32 *)(e + 0x3C) >= thr) return 2;
        return (*(s32 *)(e + 0x40) >= thr) ? 1 : 0;
    case 3:
        p = D_003876A4;
        q = D_0042A588;
        thr = *(s32 *)(q + 0x130);
        e = *(u8 **)(q + 0x260) + 120 * *(s32 *)(p + 0x64);
        if (*(s32 *)(e + 0x48) >= thr) return 5;
        if (*(s32 *)(e + 0x4C) >= thr) return 4;
        if (*(s32 *)(e + 0x50) >= thr) return 3;
        if (*(s32 *)(e + 0x54) >= thr) return 2;
        return (*(s32 *)(e + 0x58) >= thr) ? 1 : 0;
    case 4:
        t = 0;
        q = D_0042A588;
        for (k = 0; k < 4; k++) {
            t = t - *(s32 *)(q + 0x13C + 4 * k) + 6;
        }
        p = D_003876A4;
        e = *(u8 **)(q + 0x260) + 120 * *(s32 *)(p + 0x64);
        if (*(s32 *)(e + 0x60) >= t) return 5;
        if (*(s32 *)(e + 0x64) >= t) return 4;
        if (*(s32 *)(e + 0x68) >= t) return 3;
        if (*(s32 *)(e + 0x6C) >= t) return 2;
        return (*(s32 *)(e + 0x70) >= t) ? 1 : 0;
    }
    return 0;
}
