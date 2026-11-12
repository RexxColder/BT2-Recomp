#include "common.h"

void *EftHit_GetNew(void);
void ColSphere_Set(s32 arg0, void *arg1, f32 farg2);
void EftHit_SetShapeSpheres(void *arg0, s32 arg1, s32 arg2);
void func_00127128(void *arg0);
s32 func_00127F88();

void func_00181B10(void *arg0) {
    u8 *temp_s1;
    u8 *temp_v0;
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_s3;
    f32 temp_f20;

    temp_s1 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_v0 = (u8 *)EftHit_GetNew();
    *(void **)(temp_v0 + 0x60) = arg0;
    temp_a0 = *(s32 *)(temp_v0 + 0x50) | 0x42;
    *(s64 *)(temp_v0 + 0x10) = *(s64 *)(temp_s1 + 0x50);
    *(s64 *)(temp_v0 + 0x18) = *(s64 *)(temp_s1 + 0x58);
    *(s64 *)(temp_v0 + 0x20) = *(s64 *)(temp_s1 + 0x60);
    *(s64 *)(temp_v0 + 0x28) = *(s64 *)(temp_s1 + 0x68);
    *(s64 *)(temp_v0 + 0x30) = *(s64 *)(temp_s1 + 0x70);
    *(s64 *)(temp_v0 + 0x38) = *(s64 *)(temp_s1 + 0x78);
    *(s64 *)(temp_v0 + 0x40) = *(s64 *)(temp_s1 + 0x80);
    *(s32 *)(temp_v0 + 0x54) = 1;
    *(s32 *)(temp_v0 + 0x50) = temp_a0;
    *(void **)(temp_v0 + 0x68) = temp_s1;
    *(s64 *)(temp_v0 + 0x48) = *(s64 *)(temp_s1 + 0x88);
    temp_f20 = *(f32 *)(temp_s1 + 0x94);
    temp_s3 = func_00127F88(temp_a0, 1);
    temp_s2 = func_00127F88();
    ColSphere_Set(temp_s3, temp_s1 + 0x60, temp_f20);
    ColSphere_Set(temp_s2, temp_s1 + 0x70, temp_f20);
    EftHit_SetShapeSpheres(temp_v0, temp_s3, temp_s2);
    func_00127128(temp_v0);
}
