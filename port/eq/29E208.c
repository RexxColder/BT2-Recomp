#include "common.h"

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);

void Vec3_RotateY(s32 arg0, s32 arg1, f32 farg0) {
    u8 fr[0x30];
    u8 *src;
    f32 c;
    f32 s;

    src = (u8 *)arg1;
    c = cosf(farg0);
    s = sinf(farg0);
    func_00312680(c, (s32)fr, arg1);
    *(f32 *)(fr + 0x10) = *(f32 *)(src + 8) * s;
    *(s32 *)(fr + 0x14) = 0;
    *(f32 *)(fr + 0x18) = -*(f32 *)(src + 0) * s;
    *(s32 *)(fr + 0x1C) = 0;
    *(s32 *)(fr + 0x20) = 0;
    *(f32 *)(fr + 0x24) = *(f32 *)(src + 4) * (1.0f - c);
    *(s32 *)(fr + 0x28) = 0;
    *(s32 *)(fr + 0x2C) = 0;
    func_00312638(arg0, (s32)fr, (s32)(fr + 0x10));
    func_00312638(arg0, arg0, (s32)(fr + 0x20));
    *(f32 *)((u8 *)arg0 + 0xC) = *(f32 *)(src + 0xC);
}
