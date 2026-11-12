#include "common.h"

extern f32 D_00385628;
extern f32 D_0038562C;
extern f32 D_00385630;
extern f32 D_00385634;

void func_001DD2E0(u8 *arg0) {
    s32 v1;
    s32 v0;
    s32 changed;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;

    v1 = *(s32 *)(arg0 + 0x40);
    v0 = v1 & 2;
    if ((v1 & 0x20) == 0) {
        f0 = *(f32 *)(arg0 + 0x8C) + *(f32 *)(arg0 + 0x70);
        *(f32 *)(arg0 + 0x8C) = f0;
        if (f0 >= 128.0f) {
            v0 = v1 | 0x20;
            *(f32 *)(arg0 + 0x8C) = 128.0f;
            *(s32 *)(arg0 + 0x40) = v0;
            v1 = v0;
            v0 = v1 & 2;
        }
    }
    if (v0 != 0) {
        f3 = *(f32 *)(arg0 + 0x8C);
        if ((v1 & 0x40) == 0) {
            v1 = v1 | 0x40;
            *(s32 *)(arg0 + 0x40) = v1;
            *(f32 *)(arg0 + 0x70) = -f3 / 5.0f;
            *(f32 *)(arg0 + 0x64) = -*(f32 *)(arg0 + 0xC) / 5.0f;
        }
        *(f32 *)(arg0 + 0x8C) = f3 + *(f32 *)(arg0 + 0x70);
    }

    f1 = *(f32 *)(arg0 + 0x6C) + 0.0f;
    *(f32 *)(arg0 + 0x6C) = f1;
    if (D_00385628 <= f1) {
        *(f32 *)(arg0 + 0x6C) = f1 - D_0038562C;
    } else if (f1 <= D_00385630) {
        *(f32 *)(arg0 + 0x6C) = f1 + D_00385634;
    }

    f1 = *(f32 *)(arg0 + 0x60);
    f2 = *(f32 *)(arg0 + 0x14);
    f0 = f1 + *(f32 *)(arg0 + 0x64);
    *(f32 *)(arg0 + 0x60) = f0;
    *(f32 *)(arg0 + 0x5C) = f1 * f2;
    if (f0 < 0.0f) {
        *(f32 *)(arg0 + 0x60) = 0.0f;
    }
    *(f32 *)(arg0 + 0x68) = *(f32 *)(arg0 + 0x10) * f2;

    changed = 0;
    if ((v1 & 0x80) == 0) {
        f0 = *(f32 *)(arg0 + 0x74) + 1.0f;
        *(f32 *)(arg0 + 0x74) = f0;
        if (*(f32 *)(arg0 + 0x78) <= f0) {
            *(f32 *)(arg0 + 0x74) = *(f32 *)(arg0 + 0x78);
            v0 = v1 | 0x80;
            changed = 1;
        }
    } else {
        f0 = *(f32 *)(arg0 + 0x74) - 1.0f;
        *(f32 *)(arg0 + 0x74) = f0;
        if (f0 <= 0.0f) {
            *(f32 *)(arg0 + 0x74) = 0.0f;
            v0 = v1 & ~0x80;
            changed = 1;
        }
    }
    if (changed != 0) {
        *(s32 *)(arg0 + 0x40) = v0;
        v1 = v0;
    }

    v0 = v1 & 8;
    if ((v1 & 2) != 0 && *(f32 *)(arg0 + 0x8C) <= 0.0f) {
        v1 = v1 | 4;
        *(s32 *)(arg0 + 0x40) = v1;
        v0 = v1 & 8;
    }
    if (v0 == 0) {
        f0 = *(f32 *)(arg0 + 0x58) - 1.0f;
        *(f32 *)(arg0 + 0x58) = f0;
        if (f0 <= 0.0f) {
            *(s32 *)(arg0 + 0x40) = v1 | 2;
        }
    }
}
