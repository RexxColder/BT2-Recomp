#include "common.h"

f32 EftMath_WrapAngle(f32 farg0);
f32 cosf(f32 farg0);
void func_0014EAE8(s32 arg0, void *arg1);
void *func_001F3758(void *arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
f32 sinf(f32 farg0);
extern f32 D_00384690;

void func_00155030(u8 *arg0, u8 *arg1) {
    u8 *s0;
    u8 *v0;
    s32 s1;
    f32 f20;

    s0 = *(u8 **)(arg0 + 0x38);
    s1 = *(s32 *)((u8 *)func_001F3758(arg0) + 0x38);
    f20 = D_00384690;
    memset(s0, 0, 0xAB0);
    *(u8 **)(s0 + 0xB0) = arg1;
    *(f32 *)(s0 + 0x10) = 3.5f;
    v0 = *(u8 **)(arg1 + 0x24);
    *(f32 *)(s0 + 0x14) = *(f32 *)(v0 + 4);
    *(s32 *)(s0 + 0x30) = 0;
    *(f32 *)(s0 + 0x18) = *(f32 *)(v0 + 4);
    *(f32 *)(s0 + 0x34) = -sinf(EftMath_WrapAngle(f20));
    *(f32 *)(s0 + 0x38) = cosf(EftMath_WrapAngle(f20));
    *(f32 *)(s0 + 0x3C) = 1.0f;
    func_0014EAE8(s1, s0 + 0xB4);
}
