#include "common.h"

f32 func_00273000(s32 arg0, s32 arg1);
f32 func_00272F60(s32 arg0, s32 arg1);
extern f32 D_0038422C;

void func_00132C68(s32 arg0, s32 arg1) {
    u8 *out;
    f32 f20;
    f32 t;
    f32 n;

    out = (u8 *)arg1;
    f20 = func_00273000(arg0, arg1);
    t = func_00272F60(arg0, arg1) * D_0038422C;
    if (arg0 == 0) {
        n = -t;
        *(f32 *)(out + 0xC) = 1.0f;
        *(f32 *)(out + 0x8) = n;
        *(f32 *)(out + 0x4) = f20 - 270.0f;
        *(f32 *)(out + 0x0) = n;
        return;
    }
    *(f32 *)(out + 0x8) = t;
    *(f32 *)(out + 0xC) = 1.0f;
    *(f32 *)(out + 0x0) = t;
    *(f32 *)(out + 0x4) = f20 - 270.0f;
}
