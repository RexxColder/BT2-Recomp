#include "common.h"

extern u8 *D_003876A4 __attribute__((section(".data")));

s32 rand(void);
void *memcpy(void *arg0, void *arg1, u32 arg2);

s32 func_003D6D88(u8 *arg0) {
    u8 *p;
    u8 *t;
    u8 *s1;
    u8 *s3;
    s32 r;
    s32 a2;
    s32 m;
    s32 n;
    s32 s5;
    s32 s2;
    s32 a1;
    s32 rnd;
    s32 i;
    s32 dup;
    s32 cond;

    p = arg0;
    r = -1;
    a2 = -1;
    t = D_003876A4;

    if (*(s32 *)(t + 0x90) == 2) {
        m = *(s32 *)(t + 0x8C);
        if (m == 1) {
            r = 0x2B;
            a2 = 0x28;
        } else if (m < 2) {
            if (m == 0) {
                rnd = rand();
                r = 8;
                if ((rnd & 1) == 0) {
                    r = 11;
                }
                a2 = (r ^ 8) != 0 ? 8 : 5;
            }
        } else if (m == 2) {
            r = 0x63;
            a2 = 0x37;
        }
    } else if (*(s32 *)(t + 0x90) == 3) {
        m = *(s32 *)(t + 0x8C);
        if (m == 1) {
            r = 0x2C;
            a2 = 0x28;
        } else if (m < 2) {
            if (m == 0) {
                rnd = rand();
                r = 0x55;
                if ((rnd & 1) == 0) {
                    r = 0x58;
                }
                a2 = (r ^ 0x55) != 0 ? 0x47 : 0x46;
            }
        } else if (m == 2) {
            r = 0x67;
            a2 = 0x38;
        }
    }

    n = *(s32 *)(p + 0x331C);
    s5 = 0;
    s3 = p + 0x3330;

    while (s5 < n) {
        t = D_003876A4;

        if (s5 < *(s32 *)(t + 0x94)) {
            memcpy(s3 + 0xC, t + (s5 << 5) + 0xA0, 32);
            s5++;
            s3 += 0x20;
            continue;
        }

        /* random pick: retry (no advance) while the choice is rejected */
        for (;;) {
            s2 = rand() % *(s32 *)(p + 0x2D0);
            if (s2 >= 0x49) {
                continue;
            }
            s1 = *(u8 **)(p + 0x2D4) + 44 * s2;
            a1 = *(s32 *)(s1 + 0);
            if (*(s32 *)(s1 + 4) != 0) {
                rnd = rand() % *(s32 *)(s1 + 4);
                a1 = *(s32 *)(s1 + 8 + 4 * rnd);
            }
            if (a1 == 0x62 || a1 == 0x82 || a1 == 0x83 || a1 == 0x84 || a1 == 0x85) {
                continue;
            }
            break;
        }

        dup = 0;
        for (i = 0; i < s5; i++) {
            if (*(u16 *)(p + 0x333E + 0x20 * i) == a1) {
                dup = 1;
                break;
            }
        }
        if (dup) {
            continue;
        }

        if (*(s32 *)(t + 0x8C) == 0 && a1 == 0x7C) {
            continue;
        }

        cond = (r == -1) || (r != a1);
        if (!cond) {
            continue;
        }

        *(u16 *)(s3 + 0xE) = (u16)a1;
        *(u16 *)(s3 + 0x10) = (u16)s2;
        s5++;
        s3 += 0x20;
    }

    if (r != -1) {
        *(u16 *)(p + 0x34C4) = 22;
        *(u16 *)(p + 0x34BE) = (u16)r;
        *(u16 *)(p + 0x34BC) = (u16)(*(u16 *)(p + 0x34BC) | 4);
        *(u16 *)(p + 0x34C0) = (u16)a2;
        return 22;
    }
    return -1;
}
