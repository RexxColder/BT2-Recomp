#include "common.h"

void func_001865B8(u8 *arg0, s32 arg1, s32 arg2) {
    f32 sp0;
    f32 sp4;
    f32 f0;
    f32 f0b;
    f32 f3;
    f32 f4;
    s32 a1;
    s32 a2;
    s32 a3;
    s32 t0;
    s32 v0;
    u8 *a0;
    u8 *v1;

    a1 = arg1;
    a2 = arg2;
    if (arg1 == 0 || arg2 == 0) {
        a1 = 1;
        a2 = 1;
        v0 = 1;
    } else {
        v0 = arg1 * arg2;
    }
    if (v0 >= 0x10) {
        a2 = 0x10;
        a1 = 0x10;
    }
    t0 = 0;
    sp0 = 1.0f / (f32)a1;
    sp4 = 1.0f / (f32)a2;
    if (a2 > 0) {
        a0 = arg0 + 8;
        do {
            a3 = 0;
            if (a1 > 0) {
                v1 = a0 + 0x9C;
                f3 = sp4 * (f32)t0;
                f4 = f3 + sp4;
                do {
                    f0 = (f32)a3;
                    a3 += 1;
                    *(f32 *)(v1 - 0xC) = f3;
                    *(f32 *)(v1 - 0x4) = f4;
                    a0 += 0x10;
                    f0b = sp0 * f0;
                    *(f32 *)(v1 - 0x8) = f0b;
                    *(f32 *)(v1 + 0x0) = f0b + sp0;
                    v1 += 0x10;
                } while (a3 < a1);
            }
            t0 += 1;
        } while (t0 < a2);
    }
}
