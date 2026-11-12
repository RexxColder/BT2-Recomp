#include "common.h"

#define BE32P(q) (((u32)*(u8 *)(q) << 24) | ((u32)*(u8 *)((q) + 1) << 16) | ((u32)*(u8 *)((q) + 2) << 8) | (u32)*(u8 *)((q) + 3))

/* read K bits from the window (t1:a3, bit count t2), slow path refills a3 from t0 */
#define READ_K(K, FIELD)                                                  \
    if (t2 < 32 - (K)) {                                                  \
        FIELD = (s32)(t1 >> (32 - (K)));                                  \
        t1 = t1 << (K);                                                   \
        t2 += (K);                                                        \
    } else {                                                              \
        n = t2 + (K) - 32;                                                \
        if (n != 0) {                                                     \
            FIELD = (s32)((t1 | (a3 >> ((K) - n))) >> (32 - (K)));        \
            t1 = a3 << n;                                                 \
        } else {                                                          \
            FIELD = (s32)(t1 >> (32 - (K)));                              \
            t1 = a3;                                                      \
        }                                                                 \
        t2 = n;                                                           \
        a3 = BE32P(t0);                                                   \
        t0 += 4;                                                          \
    }

u8 *func_002E63D8(u8 *arg0, u8 *arg1) {
    u8 *p;
    u8 *t0;
    u8 *t4;
    u32 t1;
    u32 a3;
    s32 t2;
    s32 v0;
    s32 v1;
    s32 a0;
    s32 n;

    p = arg0 + 0x160;
    t4 = arg1;
    *(s32 *)(p + 0x43C) = *(s32 *)(p + 0x43C) + 1;
    *(s32 *)(p + 0x420) = 2;
    *(s32 *)(p + 0x4A4) = 0;
    *(s32 *)(p + 0x4A8) = 0;
    *(s32 *)(p + 0x4AC) = 0;
    a0 = *(s32 *)(p + 0x308);
    if (a0 != 0) {
        if (a0 != 8) {
            v0 = *(s32 *)(p + 0x494);
            goto L6424;
        }
    }
    /* L6414 */
    if (*(s32 *)(p + 0x30C) == 0) {
        v0 = -4;
        goto L6430;
    }
    v0 = *(s32 *)(p + 0x494);
L6424:
    v0 += 1;
    *(s32 *)(p + 0x494) = v0;
    v0 = -4;
L6430:
    t0 = (u8 *)((u32)t4 & (u32)v0);
    v1 = (s32)(t4 - t0);
    t2 = v1 << 3;
    t1 = BE32P(t0);
    a3 = BE32P(t0 + 4);
    t0 += 8;

    /* 32-bit read into 0xB8 */
    t1 = t1 << t2;
    if (t2 != 0) {
        *(s32 *)(p + 0xB8) = (s32)(t1 | (a3 >> (32 - t2)));
        t1 = a3 << t2;
    } else {
        *(s32 *)(p + 0xB8) = (s32)t1;
        t1 = a3;
    }
    a3 = BE32P(t0);
    t0 += 4;

    READ_K(1, *(s32 *)(p + 0xBC))
    READ_K(5, *(s32 *)(p + 0xC0))
    READ_K(6, *(s32 *)(p + 0xC4))
    READ_K(1, *(s32 *)(p + 0x18))
    READ_K(6, *(s32 *)(p + 0xC8))
    READ_K(6, *(s32 *)(p + 0xCC))
    READ_K(1, *(s32 *)(p + 0xD0))

    /* last 1-bit read: no window shift, no refill (t0 += 4 on the slow path) */
    if (t2 < 31) {
        *(s32 *)(p + 0xD4) = (s32)(t1 >> 31);
        t2 += 1;
    } else {
        t2 -= 31;
        if (t2 == 0) {
            *(s32 *)(p + 0xD4) = (s32)(t1 >> 31);
        } else {
            *(s32 *)(p + 0xD4) = (s32)((t1 | (a3 >> (1 - t2))) >> 31);
        }
        t0 += 4;
    }

    v1 = (s32)(t0 - t4);
    v1 = v1 << 3;
    v1 = t2 + v1;
    v0 = v1 - 0x39;
    v1 = v1 - 0x32;
    a0 = (v0 < 0);
    if (a0 != 0) {
        v0 = v1;
    }
    v0 = v0 >> 3;
    return t4 + v0;
}
