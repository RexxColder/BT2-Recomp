#include "common.h"

extern u8 *D_00387A40;
extern f32 D_00383F24;

s32 func_0020A440(s32 arg0);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);

/* 0x001164C8: per-frame update of the tracker record arg0 from the table entry arg1 (scaled by
 * 0x18580) at the base pointer D_00387A40 (+0x9C0 and +0x9C8: two floats, truncated, forming a
 * source vector with 1.0 as w). When func_0020A440(arg2) is zero the record is reset. Otherwise
 * the vector is transformed by the matrix at arg0+0x70 and the record's counters, a clamped
 * blend factor at +0x48, and the integer position words +0x54/+0x58 are updated. */
void func_001164C8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 s0 = (s32)((u32)arg1 * 0x18580u);
    f32 src[4];
    f32 dst[4];
    f32 f2;
    f32 f1;
    u8 *p;

    if (func_0020A440(arg2) == 0) {
        *(s32 *)(arg0 + 0x50) = 0;
        *(f32 *)(arg0 + 0x4C) = 31.0f;
        *(s32 *)(arg0 + 0x48) = 0;
        *(s32 *)(arg0 + 0x54) = 0;
        *(s32 *)(arg0 + 0x58) = 0;
        return;
    }

    p = (u8 *)(s32)(s0 + *(s32 *)D_00387A40);
    src[0] = (f32)(s32)*(f32 *)(p + 0x9C0);
    ((s32 *)src)[1] = 0;
    p = (u8 *)(s32)(s0 + *(s32 *)D_00387A40);
    src[2] = (f32)(s32)*(f32 *)(p + 0x9C8);
    src[3] = 1.0f;

    sceVu0ApplyMatrix((s32)dst, (s32)(arg0 + 0x70), (s32)src);

    f2 = *(f32 *)(arg0 + 0x48);
    f1 = (45.0f - f2) * D_00383F24;
    *(s32 *)(arg0 + 0x50) = 1;
    *(s32 *)(arg0 + 0x5C) = 0xFF;
    *(s32 *)(arg0 + 0x54) = (s32)dst[0];
    *(s32 *)(arg0 + 0x58) = (s32)dst[1];
    *(f32 *)(arg0 + 0x4C) = 44.0f;
    f2 = f2 + f1;
    *(f32 *)(arg0 + 0x48) = f2;
    if (44.0f < f2) {
        *(s32 *)(arg0 + 0x50) = 0;
        *(s32 *)(arg0 + 0x48) = 0;
    }
}
