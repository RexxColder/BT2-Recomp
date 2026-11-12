#include "common.h"

extern s16 D_0037AF88[] __attribute__((section(".data")));

s32 func_002DCE50(s32 arg0);
s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#define B8(a) (*(u8 *)(a))
#define BE32(a) (((u32)B8(a) << 24) | ((u32)B8((a) + 1) << 16) | ((u32)B8((a) + 2) << 8) | (u32)B8((a) + 3))
#define SLLV(x, n) ((u32)(x) << ((n) & 31))
#define SRLV(x, n) ((u32)(x) >> ((n) & 31))

s32 func_002DD6A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 a3;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 v0;
    s32 v1;
    s32 c;

    s1 = arg0;
    s2 = arg1;
    a2 = arg2;
    t0 = arg0 & ~3;
    t1 = (arg0 - t0) * 8;
    t2 = BE32(t0);
    t0 += 4;
    a3 = BE32(t0);
    t0 += 4;
    t2 = SLLV(t2, t1);
    if (t1 != 0) {
        a1 = t2 | SRLV(a3, -t1);
        t2 = SLLV(a3, t1);
    } else {
        a1 = t2;
        t2 = a3;
    }
    a3 = BE32(t0);
    t0 += 4;
    if (a1 != 0x101) {
        return 0;
    }
    if (t1 < 0x1B) {
        t1 += 5;
        t2 = t2 << 5;
    } else {
        t1 -= 0x1B;
        t2 = a3;
        v1 = SLLV(a3, t1);
        a3 = BE32(t0);
        t0 += 4;
        if (t1 != 0) {
            t2 = v1;
        }
    }
    /* DD814 */
    a1 = (u32)t2 >> 31;
    if (t1 != 0x1F) {
        t1 += 1;
        t2 = t2 << 1;
    } else {
        t2 = a3;
        a3 = BE32(t0);
        t0 += 4;
        t1 = 0;
    }
    /* DD870 */
    if (a1 != 0) {
        return 0;
    }
    a1 = (u32)t2 >> 31;
    if (t1 != 0x1F) {
        t1 += 1;
        t2 = t2 << 1;
    } else {
        t2 = a3;
        t1 = 0;
        a3 = BE32(t0);
        t0 += 4;
    }
    /* DD8D0 */
    if (a1 == 0) {
        return 0;
    }
    a1 = (u32)t2 >> 27;
    if (!(t1 < 0x1C)) {
        a1 |= SRLV(a3, 0x3B - t1);
    }
    /* DD8F4 */
    if (a1 != 7) {
        return 0;
    }
    t1 += 5;
    if (t1 < 0x20) {
        t2 = t2 << 5;
    } else {
        t1 -= 0x20;
        t2 = SLLV(a3, t1);
        a3 = BE32(t0);
        t0 += 4;
    }
    /* DD950 */
    a2 -= 1;
    t3 = 0x35;
    a0 = 8;
    v0 = (t1 < 0x16);
    for (;;) {
        /* DD960 */
        a1 = (u32)t2 >> 21;
        if (v0 == 0) {
            v0 = t3 - t1;
            a1 |= SRLV(a3, v0);
        }
        /* DD974 */
        v1 = a2 - 1;
        if (a1 == a0) {
            t1 += 0xB;
            v0 = (t1 < 0x20);
            if (v0 != 0) {
                t2 = t2 << 11;
            } else {
                t1 -= 0x20;
                t2 = SLLV(a3, t1);
                a3 = BE32(t0);
                t0 += 4;
            }
            /* DD9CC */
            a2 -= 0x21;
            c = (a2 < 0x22);
            v0 = (t1 < 0x16);
            if (c == 0) {
                continue;
            }
            v1 = a2 - 1;
        }
        break;
    }
    /* DD9E0 */
    v1 = ((u32)v1 < 0x21);
    if (v1 == 0) {
        return 0;
    }
    a2 = D_0037AF88[a2];
    a0 = a2 & 0xFF;
    v1 = 0x20 - a0;
    a1 = SRLV(t2, v1);
    v0 = (t1 < v1);
    if (v0 == 0) {
        v0 = t1 + a0;
        t1 = v0 - 0x20;
        if (t1 == 0) {
            t2 = a3;
        } else {
            v0 = a0 - t1;
            v0 = SRLV(a3, v0);
            t2 = t2 | v0;
            a1 = SRLV(t2, v1);
            t2 = SLLV(a3, t1);
        }
    } else {
        t2 = SLLV(t2, a0);
        t1 += a0;
        goto L_DDA80;
    }
    /* DDA38 */
    a3 = BE32(t0);
    t0 += 4;
L_DDA80:
    v1 = a2 >> 8;
    if (a1 != v1) {
        return 0;
    }
    v0 = (t1 < 0x1C);
    a1 = (u32)t2 >> 27;
    if (v0 == 0) {
        a1 |= SRLV(a3, 0x3B - t1);
    }
    /* DDAA8 */
    if (a1 != 7) {
        return 0;
    }
    t1 += 5;
    c = (t1 < 0x20);
    v0 = t1 + 7;
    if (c == 0) {
        t1 -= 0x20;
        t0 += 4;
        v0 = t1 + 7;
    }
    /* DDAD0 */
    v0 = v0 >> 3;
    v0 = t0 + v0;
    a0 = v0 - 8;
    a1 = a0 - s1;
    v0 = (s2 < a1);
    s3 = 3;
    if (v0 != 0) {
        return 0;
    }
    a1 = s2 - a1;
    for (;;) {
        /* DDB34 */
        s0 = func_002DCFE8(a0, a1, 0xCC, a3);
        if (s0 == 0) {
            return 0;
        }
        a0 = s0;
        v0 = func_002DCE50(a0);
        a0 = s0 + 1;
        a2 = v0;
        v0 = s0 - s1;
        v1 = a2 & 4;
        t0 = a2 & 0x40;
        a3 = v0;
        a1 = v0 + 1;
        if (v1 != 0) {
            v0 = B8(s0 + 5) & 3;
            v1 = (B8(s0 + 6) >> 7) & 1;
            v0 = (v0 << 1) | v1;
            if (v0 != s3) {
                return 0;
            }
            a1 = s2 - a1;
            continue;
        }
        /* DDB98 */
        a1 = a3 + 1;
        if (t0 != 0) {
            a0 = s0 + 1;
            a1 = s2 - a1;
            continue;
        }
        break;
    }
    /* DDBA8 */
    a0 = s0 - s1;
    if ((a2 & 0x80) != 0) {
        a1 = a0 + 4;
        v1 = (s2 < a1);
        if (v1 != 0) {
            return 0;
        }
        return 1;
    }
    /* DDAF8 */
    if ((a2 & 8) == 0) {
        return 0;
    }
    if ((B8(s0 + 7) & 0x40) == 0) {
        return 0;
    }
    v0 = s0 - s1;
    a1 = v0 + 7;
    v1 = (s2 < a1);
    if (v1 == 0) {
        return 1;
    }
    return 0;
}
