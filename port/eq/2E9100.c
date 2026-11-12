#include "common.h"

s32 func_002F8E20(s32 a0);

void func_002E9100(u8 *arg0) {
    u8 *s1;
    u8 *s2;
    u8 *t2;
    u8 *t3;
    u8 *t3b;
    u8 *src;
    u8 *dst;
    s32 v1;
    s32 a3;
    s32 t1;
    s32 t0;
    s32 w;
    s32 q;
    s32 a0v;

    s1 = arg0 + 0x48;
    v1 = *(s32 *)(arg0 + 4);
    s2 = *(u8 **)(arg0 + 0x48);
    if (v1 == 1) {
        if (func_002F8E20(*(s32 *)(arg0 + 8)) != 0) {
            v1 = *(s32 *)(arg0 + 4);
        } else {
            void (*fn1)(s32, void *, void *, void *) = *(void (**)(s32, void *, void *, void *))(arg0 + 0x78);
            fn1(*(s32 *)(arg0 + 0x7C), arg0 + 0x68, arg0 + 0x6C, arg0 + 0x70);
            a3 = *(s32 *)(s1 + 0x20);
            w = *(s32 *)(s1 + 0x24);
            t1 = *(s32 *)(s1 + 0x18) - a3;
            t1 = (w < t1) ? w : t1;
            q = *(s32 *)(s1 + 4);
            t1 = (q < t1) ? q : t1;
            t3 = *(u8 **)(s1 + 0x14);
            t2 = t3 + a3 * 2;
            if (*(s8 *)(arg0 + 0xE) == 2) {
                t3b = t3 + ((*(s32 *)(s1 + 0x1C) + a3) * 2);
                t0 = 0;
                if (t1 > 0) {
                    src = s2;
                    do {
                        a0v = t0 * 2;
                        *(u16 *)(t2 + a0v) = (u16)(src[0] | (src[2] << 8));
                        t0 += 1;
                        *(u16 *)(t3b + a0v) = (u16)(src[1] | (src[3] << 8));
                        src += 4;
                    } while (t0 < t1);
                }
            } else {
                t0 = 0;
                if (t1 > 0) {
                    src = s2;
                    dst = t2;
                    do {
                        w = (src[1] << 8) | src[0];
                        t0 += 1;
                        *(u16 *)dst = (u16)w;
                        src += 2;
                        dst += 2;
                    } while (t0 < t1);
                }
            }
            v1 = 2;
            *(s32 *)(arg0 + 4) = 2;
            *(s32 *)(arg0 + 0x90) = t1;
            *(s32 *)(arg0 + 0x94) = t1 * (s8)arg0[0xE] * 2;
        }
    }
    if (v1 == 2) {
        void (*fn2)(s32, s32, s32) = *(void (**)(s32, s32, s32))(arg0 + 0x80);
        fn2(*(s32 *)(arg0 + 0x84), *(s32 *)(arg0 + 0x94), *(s32 *)(arg0 + 0x90));
        *(s32 *)(arg0 + 4) = 3;
    }
}
