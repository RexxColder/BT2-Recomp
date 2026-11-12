#include "common.h"

s32 func_0013B350(f32 *out);

s32 EftWaterRing_Update(void *arg0) {
    f32 sp[4];
    u8 *p;
    s32 flags;
    s32 r;
    f32 f0;
    f32 f1;
    s32 nf;

    p = (u8 *)arg0;
    flags = *(s32 *)(p + 0x3C);
    if (flags & 1) {
        f0 = *(f32 *)(p + 0x30) - 1.0f;
        *(f32 *)(p + 0x30) = f0;
        if (f0 <= 0.0f) {
            flags = (flags | 2) & ~1;
            *(f32 *)(p + 0x30) = 0.0f;
            *(s32 *)(p + 0x3C) = flags;
        }
    }
    if (flags & 2) {
        r = func_0013B350(sp);
        if (r != 0) {
            *(f32 *)(p + 0x4) = sp[0] - 4.0f;
        }
        f0 = *(f32 *)(p + 0x14);
        f1 = f0 * *(f32 *)(p + 0x18);
        flags = *(s32 *)(p + 0x3C);
        *(f32 *)(p + 0x10) = *(f32 *)(p + 0x10) + f0;
        *(f32 *)(p + 0x14) = f0 + f1;
        if (!(flags & 0x40)) {
            if (flags & 4) {
                f0 = *(f32 *)(p + 0x1C) + *(f32 *)(p + 0x20);
                *(f32 *)(p + 0x1C) = f0;
                if (*(f32 *)(p + 0x24) <= f0) {
                    nf = flags & ~4;
                    f1 = *(f32 *)(p + 0x24);
                    *(f32 *)(p + 0x1C) = f1;
                    *(s32 *)(p + 0x3C) = nf;
                    if (flags & 8) {
                        *(f32 *)(p + 0x24) = 0.0f;
                        *(f32 *)(p + 0x20) = f1 / (*(f32 *)(p + 0x2C) * 30.0f);
                    }
                    flags = nf;
                }
            } else if (flags & 8) {
                f0 = *(f32 *)(p + 0x1C) - *(f32 *)(p + 0x20);
                *(f32 *)(p + 0x1C) = f0;
                if (f0 <= *(f32 *)(p + 0x24)) {
                    *(f32 *)(p + 0x1C) = *(f32 *)(p + 0x24);
                    flags = (flags & ~8) | 0x40;
                    *(s32 *)(p + 0x3C) = flags;
                }
            }
        }
    }
    if (flags & 0x40) {
        f0 = *(f32 *)(p + 0x1C) - *(f32 *)(p + 0x20);
        *(f32 *)(p + 0x1C) = f0;
        if (f0 <= 0.0f) {
            *(f32 *)(p + 0x1C) = 0.0f;
            flags = flags | 0x80;
            *(s32 *)(p + 0x3C) = flags;
        }
    }
    return (flags & 0x80) != 0;
}
