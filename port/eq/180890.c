#include "common.h"

s32 BtlScene_IsEffectStopped(s32 arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);
f32 EftMath_WrapAngle(f32 farg0);

void func_00180890(u8 *arg0) {
    u8 *s0;
    s32 v;
    s32 flags;
    s32 b8;
    f32 f0;
    f32 f2;
    f32 f12;
    f32 lim;

    s0 = *(u8 **)(arg0 + 0x38);

    if (BtlScene_IsEffectStopped(*(s32 *)(s0 + 0x58), *(u8 *)(s0 + 0x4C)) != 0) {
        return;
    }
    v = *(s32 *)(s0 + 0x54) - 1;
    *(s32 *)(s0 + 0x54) = v;
    if (v > 0) {
        return;
    }

    f2 = *(f32 *)(s0 + 0x3C);
    f0 = *(f32 *)(s0 + 0x20) + f2;
    *(s32 *)(s0 + 0x54) = 0;
    *(f32 *)(s0 + 0x20) = f0;
    if (1.0f < f0) {
        *(f32 *)(s0 + 0x20) = 1.0f;
    }

    if (*(f32 *)(s0 + 0x40) <= *(f32 *)(s0 + 0x20)) {
        flags = *(s32 *)(s0 + 0x48);
        if (!(flags & 8)) {
            *(s32 *)(s0 + 0x48) = flags | 8;
            *(f32 *)(s0 + 0x3C) = f2 * *(f32 *)(s0 + 0x44);
        }
        b8 = 1;
    } else {
        b8 = (*(s32 *)(s0 + 0x48) & 8) != 0;
    }

    if (b8) {
        lim = *(f32 *)(s0 + 0x34);
        f0 = *(f32 *)(s0 + 0x24) + *(f32 *)(s0 + 0x30);
        *(f32 *)(s0 + 0x24) = f0;
        if (f0 <= lim) {
            *(f32 *)(s0 + 0x24) = lim;
        }
    }

    f12 = *(f32 *)(s0 + 0x10) + *(f32 *)(s0 + 0x14);
    *(f32 *)(s0 + 0x10) = f12;
    *(f32 *)(s0 + 0x10) = EftMath_WrapAngle(f12);

    flags = *(s32 *)(s0 + 0x48);
    if (flags & 2) {
        f0 = *(f32 *)(s0 + 0x18) - *(f32 *)(s0 + 0x1C);
        *(f32 *)(s0 + 0x18) = f0;
        if (f0 <= 0.0f) {
            flags = flags & ~1;
            *(s32 *)(s0 + 0x48) = flags;
        }
    }
    if (flags & 4) {
        BtlTask_SetDead((s32)arg0);
    }
}
