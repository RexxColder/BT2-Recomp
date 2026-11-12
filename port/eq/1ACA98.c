#include "common.h"

extern f32 D_00384F0C;

void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
f32 func_00273048(void);
s32 func_0020B3D0(s32 arg0);
void func_00208798(s32 arg0, s32 arg1);
s32 func_0019F3B0(void *arg0, s32 arg1);
void func_00210000(s32 arg0, s32 arg1);
f32 EftMath_WrapAngle(f32 farg0);
s32 rand(void);

/* 0x001ACA98 (per-frame object update). The object's sub-record (obj+0x38) keeps a 16-bit frame counter at +0xE4,
 * a position/velocity pair (+0x50 with +0x70 added, +0x74 + +0xE0), a 16-bit count at +0xE6, flags at +0xC0 (0x2
 * copy, 0x8 and 0x100 set by the timing tests, 0x200 selects a counter at +0xC4, 0x400 a re-arm with a random
 * animation id, 0x40 cleared), an angle at +0xD8 (WrapAngle of (+0xDC mod 360)) and a 16-bit counter at +0xEA that
 * ends the update when it reaches zero. Returns 1 only when the +0xEA counter expires with the position close enough
 * (sub-record vs. the target from func_00208798). */
s32 func_001ACA98(u8 *obj) {
    u8 *o;
    u8 *s1;
    u32 flags;
    s32 v0;
    s32 v1;
    s32 r;
    s32 a1;
    s32 prod;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 dist;
    f32 d0;
    f32 d1;
    f32 d2;
    f32 wrap;
    f32 tmp[4];
    f32 out[4];

    o = *(u8 **)(obj + 0x38);
    s1 = o + 0x50;

    *(u16 *)(o + 0xE4) = (u16)(*(u16 *)(o + 0xE4) + 1);
    if (*(s32 *)(o + 0x11C) == -1) {
        *(u32 *)(o + 0xC0) = *(u32 *)(o + 0xC0) | 8;
    }

    flags = *(u32 *)(o + 0xC0);
    if ((flags & 2) != 0) {
        func_00129C28((s32)(o + 0x60), (s32)s1);
        flags = *(u32 *)(o + 0xC0);
    }
    *(u32 *)(o + 0xC0) = flags | 2;

    Vec3_Add((s32)s1, (s32)s1, (s32)(o + 0x70));

    f0 = *(f32 *)(o + 0x74) + *(f32 *)(o + 0xE0);
    v0 = (s32)*(u16 *)(o + 0xE6) - 1;
    *(u16 *)(o + 0xE6) = (u16)v0;
    *(f32 *)(o + 0x74) = f0;
    if ((s32)((u32)v0 << 16) <= 0) {
        *(u32 *)(o + 0xC0) = *(u32 *)(o + 0xC0) | 0x100;
    }

    f1 = func_00273048();
    if (f1 < *(f32 *)(o + 0x54)) {
        *(u32 *)(o + 0xC0) = *(u32 *)(o + 0xC0) | 0x100;
    }

    v0 = func_0020B3D0((s32)*(s16 *)(o + 0x12));
    func_00208798(v0, (s32)out);

    d0 = out[0] - *(f32 *)(o + 0x50);
    tmp[0] = d0;
    d1 = out[1] - *(f32 *)(o + 0x54);
    tmp[1] = d1;
    d2 = out[2] - *(f32 *)(o + 0x58);
    tmp[2] = d2;
    f1 = d0 * d0 + d1 * d1 + d2 * d2;
    dist = __builtin_sqrtf(f1);
    if (dist < 28.0f) {
        *(u32 *)(o + 0xC0) = *(u32 *)(o + 0xC0) | 0x100;
    }

    flags = *(u32 *)(o + 0xC0);
    if ((flags & 0x200) == 0) {
        v1 = (s32)*(s16 *)(o + 0xE4);
        a1 = (s32)*(f32 *)(o + 0xDC);
        prod = v1 * a1;
        r = prod % 360;
        f0 = (f32)r / 180.0f;
        f0 = f0 * D_00384F0C;
        wrap = EftMath_WrapAngle(f0);
        *(f32 *)(o + 0xD8) = wrap;
    } else {
        f0 = (f32)*(s32 *)(o + 0xC4) - 1.0f;
        *(s32 *)(o + 0xC4) = (s32)f0;
    }

    flags = *(u32 *)(o + 0xC0);
    if ((flags & 0x400) == 0) {
        f1 = (f32)*(s32 *)(o + 0xC4);
        if (f1 <= 0.0f || (flags & 0x100) != 0) {
            a1 = *(s32 *)(o + 0xC8);
            *(s32 *)(o + 0xC4) = 0;
            func_0019F3B0(s1, a1);
            f20 = 28.0f;
            r = rand();
            a1 = ((r & 2) != 0) ? 0x1B : 0x11;
            func_00210000((s32)s1, a1);
            flags = (*(u32 *)(o + 0xC0) & ~0x40u) | 0x400u;
            *(u32 *)(o + 0xC0) = flags;
            *(f32 *)(o + 0xD4) = f20;
        }
        flags = *(u32 *)(o + 0xC0);
        if ((flags & 0x400) == 0) {
            return 0;
        }
    }

    v1 = (s32)*(s16 *)(o + 0xEA);
    f0 = (f32)v1 - 1.0f;
    v1 = (s32)f0;
    *(u16 *)(o + 0xEA) = (u16)v1;
    if ((f32)(s16)v1 <= 0.0f) {
        *(u32 *)(o + 0xC0) = flags | 8;
        *(u16 *)(o + 0xEA) = 0;
        return 1;
    }
    return 0;
}
