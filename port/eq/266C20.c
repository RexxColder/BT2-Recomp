#include "m2c_macros.h"

void func_00267550(void *ctx, s32 a1, s32 a2);

void func_00266C20(void *a0, u8 *o) {
    s32 k;
    s32 n;
    s32 found = -1;
    s32 ty;
    f32 t;
    u8 *tbl;

    if (*(u8 *)(o + 0x30) == 0) {
        return;
    }
    t = *(f32 *)(o + 0x40);
    if (0.0f <= t) {
        tbl = *(u8 **)(o + 0x34);
        n = *(u16 *)(o + 0x3E);
        k = *(u16 *)(o + 0x3C);
        if (k < n - 1) {
            for (;;) {
                if ((f32)*(u16 *)(tbl + k * 4) <= t && t < (f32)*(u16 *)(tbl + k * 4 + 4)) {
                    found = k;
                    *(u16 *)(o + 0x3C) = (u16)k;
                    break;
                }
                k = (u16)(k + 1);
                if (!(k < n - 1)) {
                    break;
                }
            }
        }
        if (*(f32 *)(o + 0x44) < t || found == -1) {
            func_00267550(a0, 0, 0);
            return;
        }
        ty = *(u16 *)(tbl + found * 4 + 2);
        if (ty == 0) {
            func_00267550(a0, 1, 0);
        } else if (ty == 1) {
            if (*(s32 *)(o + 0x10) != 3) {
                func_00267550(a0, 3, 0);
            }
        } else if (*(s32 *)(o + 0x10) != 4) { /* asm 0x266D48: `lw v1,16(s0)` in the delay slot of `bne`: compares the
                                                   current state o->0x10, not the table type (class 11) */
            func_00267550(a0, 4, 0);
        }
    }
    *(f32 *)(o + 0x40) = *(f32 *)(o + 0x40) + *(f32 *)(o + 0x20);
}
