#include "common.h"

s32 rand(void);

void func_0027FAC8(void *arg0, s32 arg1) {
    u8 *s3;
    u8 *s0;
    u8 *s2;
    u8 *a1p;
    u8 *a2p;
    s32 s5;
    s32 s6;
    s32 s1;
    s32 s4;
    s32 a3;
    s32 a0;
    s32 dlt;
    s32 t;
    f32 x;
    f32 d;
    f32 k;

    s3 = (u8 *)arg0;
    s5 = *(s32 *)(s3 + 0x60C);
    s6 = *(s32 *)(s3 + 0x610);
    if ((u8)arg1 != 0) {
        s5 = s5 / 2;
    }
    a0 = *(s32 *)(s3 + 0x604);
    if ((a0 % *(s32 *)(s3 + 0x600)) == 0) {
        if (s6 > 0) {
            s4 = s6;
            a3 = 0;
            do {
                s0 = s3 + a3;
                s2 = s0 + 0x180;
                if (s5 > 0) {
                    s1 = s5;
                    do {
                        s1 -= 1;
                        *s0 = (u8)((rand() % (*(s32 *)(s3 + 0x614) * 2)) - *(u8 *)(s3 + 0x614));
                        s0 += 1;
                        *s2 = (u8)((rand() % (*(s32 *)(s3 + 0x618) * 2)) - *(u8 *)(s3 + 0x618));
                        s2 += 1;
                    } while (s1 != 0);
                }
                s4 -= 1;
                a3 += 0xC;
            } while (s4 != 0);
        }
    }

    if (s6 > 0) {
        s4 = s6;
        a3 = 0;
        do {
            s0 = s3 + a3;
            s2 = s0 + 0x180;
            a2p = s0 + 0x300;
            a1p = s0 + 0x480;
            if (s5 > 0) {
                s1 = s5;
                do {
                    k = *(f32 *)(s3 + 0x608);
                    s1 -= 1;
                    dlt = (s32)(*(s8 *)s0) - (s32)(*(s8 *)a2p);
                    s0 += 1;
                    x = (f32)dlt * k;
                    t = (s32)x;
                    d = x - (f32)t;
                    if (d > 0.5f || (d == 0.5f && (t & 1))) {
                        t += 1;
                    } else if (d < -0.5f || (d == -0.5f && (t & 1))) {
                        t -= 1;
                    }
                    *a2p = (u8)(*a2p + t);
                    a2p += 1;

                    dlt = (s32)(*(s8 *)s2) - (s32)(*(s8 *)a1p);
                    s2 += 1;
                    x = (f32)dlt * k;
                    t = (s32)x;
                    d = x - (f32)t;
                    if (d > 0.5f || (d == 0.5f && (t & 1))) {
                        t += 1;
                    } else if (d < -0.5f || (d == -0.5f && (t & 1))) {
                        t -= 1;
                    }
                    *a1p = (u8)(*a1p + t);
                    a1p += 1;
                } while (s1 != 0);
            }
            s4 -= 1;
            a3 += 0xC;
        } while (s4 != 0);
    }
    *(s32 *)(s3 + 0x604) = *(s32 *)(s3 + 0x604) + 1;
}
