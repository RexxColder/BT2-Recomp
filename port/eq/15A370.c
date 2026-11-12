#include "common.h"

u8 *EftHit_GetNew(void);
void ColSphere_Set(s32 arg0, u8 *arg1, f32 farg0);
void EftHit_SetShapeSpheres(u8 *arg0, s32 arg1, s32 arg2);
void func_00127128(u8 *arg0);
s32 func_00127F88(void);
f32 func_00152958(u8 *arg0);

void func_0015A370(u8 *arg0) {
    f32 temp_f20;
    s32 temp_s2;
    s32 temp_s3;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s1 = EftHit_GetNew();
    temp_f20 = *(f32 *)(temp_s0 + 0xC) * func_00152958(temp_s0 + 0x84);
    *(s64 *)(temp_s1 + 0x10) = *(s64 *)(temp_s0 + 0x40);
    temp_f20 = temp_f20 * *(f32 *)(temp_s0 + 4);
    *(s64 *)(temp_s1 + 0x18) = *(s64 *)(temp_s0 + 0x48);
    *(s64 *)(temp_s1 + 0x20) = *(s64 *)(temp_s0 + 0x50);
    *(s64 *)(temp_s1 + 0x28) = *(s64 *)(temp_s0 + 0x58);
    *(s64 *)(temp_s1 + 0x30) = *(s64 *)(temp_s0 + 0x60);
    *(s64 *)(temp_s1 + 0x38) = *(s64 *)(temp_s0 + 0x68);
    *(s64 *)(temp_s1 + 0x40) = *(s64 *)(temp_s0 + 0x70);
    *(u8 **)(temp_s1 + 0x60) = arg0;
    *(s64 *)(temp_s1 + 0x48) = *(s64 *)(temp_s0 + 0x78);
    *(s32 *)(temp_s1 + 0x64) = *(s32 *)(temp_s0 + 0x80);
    temp_s3 = func_00127F88();
    temp_s2 = func_00127F88();
    ColSphere_Set(temp_s3, temp_s0 + 0x50, temp_f20);
    ColSphere_Set(temp_s2, temp_s0 + 0x60, temp_f20);
    EftHit_SetShapeSpheres(temp_s1, temp_s3, temp_s2);
    func_00127128(temp_s1);
}
