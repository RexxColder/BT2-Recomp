#include "common.h"

void ColSeg_Set(s32 arg0, s32 arg1, s32 arg2);
s32 func_0011E1C8(s32 arg0);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);

/* 0x00124500: segment-table update on the object at arg0+0xBE0 (count at +0xBE4, cursor at +0x10, +0x14). */
void func_00124500(void *arg0) {
    u8 fr[0x40];
    u8 *obj;
    u8 *s;
    s32 s0;
    s32 s2;
    s32 s3;
    s32 v;
    s32 lim;
    f32 f20;
    f32 t;

    obj = (u8 *)arg0;
    s = obj + 0xBE0;
    if (*(s32 *)(obj + 0xBE4) <= 0) {
        return;
    }
    if (*(s32 *)(s + 0x4) < 3) {
        return;
    }
    if (*(s32 *)(s + 0x10) < 2) {
        *(s32 *)(s + 0xC) = 1;
        return;
    }
    ColSeg_Set((s32)fr, (s32)(s + 0x20 + (*(s32 *)(s + 0x10) << 4)),
               (s32)(s + 0x20 + (*(s32 *)(s + 0x14) << 4)));

    if (func_0011E1C8((s32)fr) != 0) {
        *(s32 *)(s + 0x14) += 1;
        v = *(s32 *)(s + 0x10);
        if (*(s32 *)(s + 0x14) + (signed char)s[v + 0x3E0] < v) {
            return;
        }
        *(s32 *)(s + 0x14) = 0;
        v -= 1;
        if (v < 0) {
            v = 0;
        }
        *(s32 *)(s + 0x10) = v;
        return;
    }

    lim = *(s32 *)(s + 0x10);
    if ((signed char)s[lim + 0x3E0] >= lim - *(s32 *)(s + 0x14)) {
        *(s32 *)(s + 0x14) = 0;
        v = lim - 1;
        if (v < 0) {
            v = 0;
        }
        *(s32 *)(s + 0x10) = v;
        return;
    }

    s3 = *(s32 *)(s + 0x10) - *(s32 *)(s + 0x14);
    func_00312650((s32)(fr + 0x20), (s32)(fr + 0x10), (s32)fr);
    s2 = 1;
    if (s2 < s3) {
        f20 = (f32)s3;
        do {
            t = (f32)s2 / f20;
            s0 = *(s32 *)(s + 0x10) - s2;
            func_00312680((s32)(fr + 0x30), (s32)(fr + 0x20), t);
            func_00312638((s32)(s + 0x20 + (s0 << 4)), (s32)fr, (s32)(fr + 0x30));
            s[0x3C0 + s0] |= 0x0F;
            s2 += 1;
        } while (s2 < s3);
    }

    s2 = 0;
    s[0x3C0 + *(s32 *)(s + 0x10)] |= 0x0C;
    if (s3 > 0) {
        do {
            s0 = *(s32 *)(s + 0x10) - s2;
            v = s3 - s2;
            s2 += 1;
            s[0x3E0 + s0] = (u8)v;
        } while (s2 < s3);
    }

    s2 = *(s32 *)(s + 0x4) - 1;
    lim = *(s32 *)(s + 0x10);
    if (lim < s2) {
        do {
            if ((s2 - lim) < (signed char)s[0x3E0 + s2]) {
                s[0x3E0 + s2] = (u8)(s2 - (u8)*(s32 *)(s + 0x10));
            }
            s2 -= 1;
        } while (*(s32 *)(s + 0x10) < s2);
    }

    *(s32 *)(s + 0x8) = 0;
    *(s32 *)(s + 0x10) = *(s32 *)(s + 0x4) - 1;
    *(s32 *)(s + 0x14) = 0;
}
