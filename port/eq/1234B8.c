#include "common.h"

f32 func_00123140(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_003876FC;

f32 func_001234B8(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 q = *(s32 *)(D_003876FC + 0x10);
    s32 a3 = *(s32 *)(arg0 + 0x184) * 0x10;
    s32 t0 = *(s32 *)(q + 0x48);
    s32 w = *(s32 *)(q + 0xC);
    s32 idx = arg1 * w + arg2;
    f32 f20;
    f32 f0;
    u8 b;
    f32 r;

    f20 = farg0 + 0.0f;
    f0 = *(f32 *)(*(s32 *)(q + 0x68) + idx * 4);
    b = *(u8 *)(*(s32 *)(q + 0x6C) + idx);
    f20 = f20 + f0;
    r = func_00123140(farg0, ((s32)b << 4) + t0, t0 + a3, idx, a3);
    return f20 + r;
}
