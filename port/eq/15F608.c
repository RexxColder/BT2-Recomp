#include "common.h"

s32 EftHit_GetNew(s32 arg0);
void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
s32 func_00127F88();
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);
f32 func_00152958(s32 arg0);

void func_0015F608(s32 arg0) {
    u8 *e;
    u8 *hit;
    u8 *src;
    s32 s1;
    s32 s0;
    f32 f20;
    s32 i;

    e = *(u8 **)(arg0 + 0x38);
    hit = (u8 *)EftHit_GetNew(arg0);
    src = e + 0x70;
    f20 = *(f32 *)(e + 0x1C) * func_00152958((s32)(e + 0xF4));
    if (*(s32 *)(e + 0) & 0x400) {
        src = e + 0xB0;
        *(s32 *)(hit + 0x50) = *(s32 *)(hit + 0x50) | 0x10;
    }
    for (i = 0; i < 8; i++) {
        *(s64 *)(hit + 0x10 + i * 8) = *(s64 *)(src + i * 8);
    }
    *(s32 *)(hit + 0x60) = arg0;
    *(s32 *)(hit + 0x64) = *(s32 *)(e + 0xF0);
    s1 = func_00127F88();
    s0 = func_00127F88();
    ColSphere_Set(f20, s1, (s32)(src + 0x10));
    ColSphere_Set(f20, s0, (s32)(src + 0x20));
    EftHit_SetShapeSpheres((s32)hit, s1, s0);
    func_00127128((s32)hit);
}
