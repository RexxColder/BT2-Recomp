#include "common.h"

s32 EftHit_GetNew(s32 arg0);
void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
s32 func_00127F88();
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);
extern u8 *D_00387848;

void func_001AA740(s32 arg0) {
    u8 *e;
    u8 *hit;
    u8 *a;
    s32 s2;
    s32 s3;
    f32 f20;

    e = *(u8 **)(arg0 + 0x38);
    hit = (u8 *)EftHit_GetNew(arg0);
    *(s32 *)(hit + 0x60) = arg0;
    a = e + 0x40;
    *(s64 *)(hit + 0x10) = *(s64 *)(e + 0x80);
    *(s64 *)(hit + 0x18) = *(s64 *)(e + 0x88);
    *(s64 *)(hit + 0x20) = *(s64 *)(e + 0x90);
    *(s64 *)(hit + 0x28) = *(s64 *)(e + 0x98);
    *(s64 *)(hit + 0x30) = *(s64 *)(e + 0xA0);
    *(s64 *)(hit + 0x38) = *(s64 *)(e + 0xA8);
    *(s64 *)(hit + 0x40) = *(s64 *)(e + 0xB0);
    *(s32 *)(hit + 0x54) = 0;
    *(s64 *)(hit + 0x48) = *(s64 *)(e + 0xB8);
    *(s32 *)(hit + 0x68) = (s32)a;
    *(s8 *)(hit + 0x5C) = (*(s32 *)(e + 0) >> 9) & 1;
    f20 = *(f32 *)(e + 0x2C) * *(f32 *)(*(u8 **)(D_00387848 + 8) + 4);
    s3 = func_00127F88((s32)a);
    s2 = func_00127F88();
    ColSphere_Set(f20, s3, (s32)(e + 0x90));
    ColSphere_Set(f20, s2, (s32)(e + 0xA0));
    EftHit_SetShapeSpheres((s32)hit, s3, s2);
    func_00127128((s32)hit);
}
