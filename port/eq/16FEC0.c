#include "common.h"

void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
s32 EftHit_GetNew(void);
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);
s32 func_00127F88(void);
f32 func_00152958(s32 arg0);

void func_0016FEC0(s32 arg0) {
    f32 f20;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 temp_v0;

    s2 = *(s32 *)(arg0 + 0x38);
    s3 = EftHit_GetNew();
    f20 = func_00152958(s2 + 0xD4);
    *(s64 *)(s3 + 0x10) = *(s64 *)(s2 + 0x90);
    *(s64 *)(s3 + 0x18) = *(s64 *)(s2 + 0x98);
    *(s64 *)(s3 + 0x20) = *(s64 *)(s2 + 0xA0);
    *(s64 *)(s3 + 0x28) = *(s64 *)(s2 + 0xA8);
    *(s64 *)(s3 + 0x30) = *(s64 *)(s2 + 0xB0);
    *(s64 *)(s3 + 0x38) = *(s64 *)(s2 + 0xB8);
    *(s64 *)(s3 + 0x40) = *(s64 *)(s2 + 0xC0);
    *(s32 *)(s3 + 0x60) = arg0;
    *(s64 *)(s3 + 0x48) = *(s64 *)(s2 + 0xC8);
    *(s32 *)(s3 + 0x64) = *(s32 *)(s2 + 0xD0);
    f20 = *(f32 *)(s2 + 0x1C) * f20;
    if (*(s32 *)(s2 + 0) & 0x200) {
        temp_v0 = *(s32 *)(s3 + 0x50);
        *(s32 *)(s3 + 0x50) = temp_v0 | 0x40;
        if (*(s32 *)(s2 + 0) & 0x400) {
            *(s32 *)(s3 + 0x50) = temp_v0 | 0x50;
        }
    }
    s1 = func_00127F88();
    s0 = func_00127F88();
    ColSphere_Set(f20, s1, s2 + 0xA0);
    ColSphere_Set(f20, s0, s2 + 0xB0);
    EftHit_SetShapeSpheres(s3, s1, s0);
    func_00127128(s3);
}
