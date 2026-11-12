#include "common.h"

/* refill: 4 bytes at t1 (first one signed), t1 += 4 */
#define RD4(dst)                                                                      \
    do {                                                                              \
        u8 *q_ = t1;                                                                  \
        (dst) = ((u32)(s32)(s8)q_[0] << 24) | ((u32)q_[1] << 16) | ((u32)q_[2] << 8) | (u32)q_[3]; \
        t1 += 4;                                                                      \
    } while (0)

void func_002DABF8(u8 *arg0, s32 arg1, s32 *arg2) {
    u8 *t1;
    u8 *q;
    u32 t0, t2, t3, t4, t5, a2, a3;
    s32 a1;

    q = (u8 *)(s32)((arg1 + 4) & ~3);
    a1 = arg1 - (s32)q;
    t2 = ((u32)(s32)(s8)q[0] << 24) | ((u32)q[1] << 16) | ((u32)q[2] << 8) | (u32)q[3];
    t0 = ((u32)(s32)(s8)q[4] << 24) | ((u32)q[5] << 16) | ((u32)q[6] << 8) | (u32)q[7];
    t1 = q + 8;
    a1 = (a1 + 4) * 8;
    t2 = t2 << (a1 & 31);

    if (a1 < 0x1E) {
        t5 = t2 >> 30;
        t2 = t2 << 2;
        a1 += 2;
    } else {
        a1 -= 0x1E;
        if (a1 != 0) {
            t5 = (t2 | (t0 >> 1)) >> 30;
            t2 = t0 << 1;
        } else {
            t5 = t2 >> 30;
            t2 = t0;
        }
        RD4(t0);
    }

    /* DAD04 */
    a1 += 2;
    if (a1 < 0x20) {
        t2 = t2 << 2;
    } else {
        a1 -= 0x20;
        t2 = t0 << (a1 & 31);
        RD4(t0);
    }

    /* DAD54 */
    t4 = t2 >> 29;
    if (a1 < 0x1D) {
        t2 = t2 << 3;
        a1 += 3;
    } else {
        a1 -= 0x1D;
        if (a1 != 0) {
            t4 = (t2 | (t0 >> (3 - a1))) >> 29;
            t2 = t0 << (a1 & 31);
        } else {
            t2 = t0;
        }
        RD4(t0);
    }

    /* DADD0 */
    a1 += 1;
    if (a1 < 0x20) {
        t2 = t2 << 1;
    } else {
        a1 -= 0x20;
        t2 = t0 << (a1 & 31);
        RD4(t0);
    }

    /* DAE20 */
    t3 = t2 >> 17;
    if (a1 < 0x11) {
        t2 = t2 << 15;
        a1 += 0xF;
    } else {
        a1 -= 0x11;
        if (a1 != 0) {
            t3 = (t2 | (t0 >> (0xF - a1))) >> 17;
            t2 = t0 << (a1 & 31);
        } else {
            t2 = t0;
        }
        RD4(t0);
    }

    /* DAE98 */
    a1 += 1;
    if (a1 < 0x20) {
        t2 = t2 << 1;
    } else {
        a1 -= 0x20;
        t2 = t0 << (a1 & 31);
        RD4(t0);
    }

    /* DAEE8 */
    a3 = t2 >> 17;
    if (a1 < 0x11) {
        t2 = t2 << 15;
        a1 += 0xF;
    } else {
        a1 -= 0x11;
        if (a1 != 0) {
            a3 = (t2 | (t0 >> (0xF - a1))) >> 17;
            t2 = t0 << (a1 & 31);
        } else {
            t2 = t0;
        }
        RD4(t0);
    }

    /* DAF60 */
    a1 += 1;
    if (a1 < 0x20) {
        t2 = t2 << 1;
    } else {
        a1 -= 0x20;
        t2 = t0 << (a1 & 31);
        RD4(t0);
    }

    /* DAFB0 (last refill: the asm reads its 4th byte without stepping t1) */
    a1 += 1;
    if (a1 < 0x20) {
        t2 = t2 << 1;
    } else {
        a1 -= 0x20;
        t2 = t0 << (a1 & 31);
        RD4(t0);
    }

    /* DAFF8 */
    a2 = t2 >> 10;
    if (a1 >= 0xA) {
        a1 -= 0xA;
        if (a1 != 0) {
            a2 = (t2 | (t0 >> (0x16 - a1))) >> 10;
        }
    }

    *(u32 *)(arg0 + 0x18 + 0xC) = a2;
    *(s32 *)(arg0 + 0x18 + 0x8) = (t5 == 0);
    *(s64 *)(arg0 + 0x18) = (s64)((((t4 & 7) << 30) | ((t3 & 0x7FFF) << 15) | (a3 & 0x7FFF)));
    *arg2 = 0xC;
}
