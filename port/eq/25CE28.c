#include "common.h"

extern u8 *D_00387A40;

void func_0025CE28(void *arg0, s32 arg1) {
    u8 *p;
    u8 *t6;
    u8 *a2p;
    u8 *t2;
    u8 *a2b;
    u8 *t9dummy;
    s32 s0;
    s32 t0;
    s32 t1;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 t7;
    s32 t8;
    s32 a1;
    s32 a3;
    s32 a0;
    s32 vb;
    s32 cnt;
    u8 *v0p;
    u8 *a0p;
    u8 *a2q;
    u8 *a3p;
    u8 *a1p;
    u8 *a0q;
    u8 *base;

    p = (u8 *)arg0;
    s0 = 0;
    t0 = 0;
    t6 = *(u8 **)(p + 0x4C);
    a3 = arg1 * 0x14;
    a2p = *(u8 **)(p + 0x44);
    t7 = a2p[0x2C];
    if (t7 == 0) {
        t7 = -1;
    }
    t5 = a2p[0x25];
    t8 = a2p[0x24];
    t2 = *(u8 **)(p + 0x50);

    if (*(u32 *)t6 != 0) {
        t4 = t5 << 6;
        t3 = 0x38081 + arg1 * 0x14;
        if (a3 >= 0x100) {
            a3 -= 0x100;
        }
        a1 = a3 + 1;
        t5 = t8 + t5;
        do {
            if (t0 >= t8 && t0 < t5) {
                base = *(u8 **)(t6 + 0x10);
                a0 = t0 << 6;
                if (t2 != NULL) {
                    s0 = *(s32 *)(*(u8 **)(t2 + 0x10) + a0 + 0x3C) + 0x60;
                }
                t1 = 0;
                if (t7 != t0) {
                    a3 = *(s32 *)(base + a0 + 0x3C);
                    v0p = (u8 *)(a3 + 0x63);
                    a2q = (u8 *)(*(s32 *)(base + t4 + 0x3C) + 0x63);
                    cnt = 0xF;
                    vb = a1;
                    a0p = (u8 *)(s0 + 3);
                    do {
                        t1 = *v0p;
                        *v0p = (u8)vb;
                        v0p += 4;
                        *a2q = (u8)vb;
                        a2q += 4;
                        if (t2 != NULL) {
                            *a0p = (u8)vb;
                        }
                        cnt -= 1;
                        a0p += 4;
                    } while (cnt >= 0);
                }
                a1 += 1;
                *(D_00387A40 + t3 + 4) = (u8)t1;
                t3 += 1;
            }
            t0 += 1;
            t4 += 0x40;
        } while ((u32)t0 < *(u32 *)t6);
    }

    a3p = *(u8 **)(p + 0x54);
    if (a3p != NULL) {
        t0 = 0;
        a0 = *(s32 *)(a2p + 0x22) << 6;
        base = *(u8 **)(t6 + 0x10);
        t1 = *(s32 *)(base + (a2p[0x22] << 6) + 0x3C) + 0x60;
        if (*(u32 *)a3p != 0) {
            do {
                a1p = (u8 *)(t1 + 3);
                a3 = 0;
                a0q = (u8 *)(*(s32 *)(*(u8 **)(a3p + 0x10) + (t0 << 6) + 0x3C) + 0x63);
                do {
                    vb = *a1p;
                    a1p += 4;
                    a3 += 1;
                    *a0q = (u8)vb;
                    a0q += 4;
                } while (a3 < 0x10);
                t0 += 1;
            } while ((u32)t0 < *(u32 *)a3p);
        }
    }
    (void)t9dummy;
    (void)a2b;
}
