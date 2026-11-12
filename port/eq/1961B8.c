#include "common.h"

s32 EftHit_GetNew(s32 arg0);
void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
s32 func_00127F88();
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);

void func_001961B8(s32 arg0) {
    u8 *e;
    u8 *hit;
    s32 s2;
    s32 s3;
    f32 f20;
    s32 i;

    e = *(u8 **)(arg0 + 0x38);
    hit = (u8 *)EftHit_GetNew(arg0);
    *(s32 *)(hit + 0x60) = arg0;
    *(s64 *)(hit + 0x10) = *(s64 *)(e + 0xB20);
    *(s64 *)(hit + 0x18) = *(s64 *)(e + 0xB28);
    *(s64 *)(hit + 0x20) = *(s64 *)(e + 0xB30);
    *(s64 *)(hit + 0x28) = *(s64 *)(e + 0xB38);
    *(s64 *)(hit + 0x30) = *(s64 *)(e + 0xB40);
    *(s64 *)(hit + 0x38) = *(s64 *)(e + 0xB48);
    *(s64 *)(hit + 0x40) = *(s64 *)(e + 0xB50);
    *(s64 *)(hit + 0x48) = *(s64 *)(e + 0xB58);
    *(s32 *)(hit + 0x64) = *(s32 *)(e + 0xAD0 + 0x20);
    f20 = *(f32 *)(e + 0xAD0 + 0x48);
    s3 = func_00127F88((s32)(e + 0xAD0));
    s2 = func_00127F88();
    ColSphere_Set(f20, s3, (s32)(e + 0xB30));
    ColSphere_Set(f20, s2, (s32)(e + 0xB40));
    EftHit_SetShapeSpheres((s32)hit, s3, s2);
    func_00127128((s32)hit);
}
