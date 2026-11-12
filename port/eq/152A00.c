#include "common.h"

void *EftHit_GetNew(void);
void ColSphere_Set(s32 arg0, void *arg1, f32 farg2);
void EftHit_SetShapeSpheres(void *arg0, s32 arg1, s32 arg2);
void func_00127128(void *arg0);
s32 func_00127F88();
f32 func_00152958(void *arg0);

void func_00152A00(void *arg0) {
    u8 *temp_s0;
    u8 *temp_s1;
    f32 temp_f20;
    s32 temp_s2;
    s32 temp_s3;
    s64 temp_a0;

    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s1 = (u8 *)EftHit_GetNew();
    temp_f20 = *(f32 *)(temp_s0 + 0x1C) * func_00152958(temp_s0 + 0xB4);
    *(s64 *)(temp_s1 + 0x10) = *(s64 *)(temp_s0 + 0x70);
    *(s64 *)(temp_s1 + 0x18) = *(s64 *)(temp_s0 + 0x78);
    *(s64 *)(temp_s1 + 0x20) = *(s64 *)(temp_s0 + 0x80);
    *(s64 *)(temp_s1 + 0x28) = *(s64 *)(temp_s0 + 0x88);
    *(s64 *)(temp_s1 + 0x30) = *(s64 *)(temp_s0 + 0x90);
    *(s64 *)(temp_s1 + 0x38) = *(s64 *)(temp_s0 + 0x98);
    *(s64 *)(temp_s1 + 0x40) = *(s64 *)(temp_s0 + 0xA0);
    temp_a0 = *(s64 *)(temp_s0 + 0xA8);
    *(void **)(temp_s1 + 0x60) = arg0;
    *(s64 *)(temp_s1 + 0x48) = temp_a0;
    *(s32 *)(temp_s1 + 0x64) = *(s32 *)(temp_s0 + 0xB0);
    temp_s3 = func_00127F88((s32)temp_a0);
    temp_s2 = func_00127F88();
    ColSphere_Set(temp_s3, temp_s0 + 0x80, temp_f20);
    ColSphere_Set(temp_s2, temp_s0 + 0x90, temp_f20);
    EftHit_SetShapeSpheres(temp_s1, temp_s3, temp_s2);
    func_00127128(temp_s1);
}
