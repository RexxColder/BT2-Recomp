#include "common.h"

s32 func_0012B9B0(void);
s32 func_001ED2D8(s32 arg0, s32 arg1, s32 arg2);
void func_0012D868(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_001EDD98(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7,
                   s32 p8, s32 p9, s32 p10, s32 p11, s32 p12, s32 p13, s64 p14);

/* Tests one vertex record for the clip path: the record needs a positive w-like word, both coordinates
 * within the 16-bit window, and returns 1 unless the third word is below one. */
static s32 vtest(s32 e0, s32 e1, s32 e2) {
    s32 t = 1;

    if (e2 > 0) {
        if (!(65519 < e0) && e0 > 0) {
            if (!(65519 < e1)) {
                t = (e1 < 1);
            }
        }
    }
    return t;
}

/* Clip and emit loop over the projected records: clamps the 24-bit fields, averages the first record,
 * and for each record pair either skips (both in range) or hands the pair to func_001EDD98. Always
 * returns 0. */
s32 func_001ED648(s32 a1, s32 a2, u8 a3, s32 a4, u8 a5, u8 a6, u8 a7, s64 a8, s32 a9) {
    u8 sp[0x1D0];
    s32 s1 = 4;
    s32 s3 = 3;
    s32 s0;
    s32 s2 = a1;
    s32 s4 = a2;
    s32 base;
    s32 p;
    s32 a1v;
    s32 a0v;
    s32 v0v;
    s32 a3v;
    s32 t;
    s32 idx;

    base = func_0012B9B0();
    s0 = base;
    do {
        s3 = func_001ED2D8(s0, s3, s2);
        s0 = s0 + 16;
        s1 = s1 - 1;
    } while (s1 >= 0);

    if (s3 == 0) {
        return 0;
    }

    func_0012D868((s32)(sp + 0x40), s4, s2, s3, (s32)(sp + 0xD0), s2 + 0x90);

    s1 = 2;
    s0 = (s32)(sp + 0x68);
    while (s1 < s3) {
        p = s0;
        a1v = *(s32 *)(sp + 0x48);
        a0v = *(s32 *)(p - 16);
        v0v = *(s32 *)p;
        a3v = (a1v + a0v + v0v) / 3;
        a3v = a3v >> 8;
        if (a7 != 0) {
            a3v = 0x1000 - a3v;
        }
        if (a1v > 0xFFFFFF) {
            *(s32 *)(sp + 0x48) = 0xFFFFFF;
            a0v = *(s32 *)(p - 16);
        }
        if (a0v > 0xFFFFFF) {
            *(s32 *)(p - 16) = 0xFFFFFF;
        }
        if (v0v > 0xFFFFFF) {
            *(s32 *)p = 0xFFFFFF;
        }

        idx = 16 * s1;
        t = vtest(*(s32 *)(sp + 0x40), *(s32 *)(sp + 0x44), *(s32 *)(sp + 0x48));
        if (t != 0) {
            t = vtest(*(s32 *)(sp + 0x40 + idx - 16), *(s32 *)(sp + 0x44 + idx - 16),
                      *(s32 *)(sp + 0x48 + idx - 16));
        }
        if (t != 0) {
            t = vtest(*(s32 *)(sp + 0x40 + idx), *(s32 *)(sp + 0x44 + idx),
                      *(s32 *)(sp + 0x48 + idx));
        }

        if (t != 0) {
            s1 = s1 + 1;
        } else {
            func_001EDD98((s32)(sp + 0x40), (s32)(sp + 0x40 + idx - 16), (s32)(sp + 0x40 + idx),
                          s2 + 0x120, s2 + idx + 272, s2 + idx + 288, (s32)(sp + 0xD0),
                          (s32)(sp + 0xD0 + idx - 16),
                          (s32)(sp + 0xD0) + idx, a5, a6, a3, a4, a3v + a9, a8);
            s1 = s1 + 1;
        }
        s0 = s0 + 16;
    }
    return 0;
}
