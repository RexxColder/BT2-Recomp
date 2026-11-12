#include "common.h"

u8 *EftHit_GetNew();
f32 func_00152958(void *arg0);
void ColCapsule_Set(f32 farg0, s32 arg1, void *arg2, void *arg3);
void ColSphere_Set(f32 farg0, s32 arg1, void *arg2);
s32 EftHitArena_AllocBox();
s32 func_00127F88();
void EftHit_SetShapeBoxes(void *arg0, s32 arg1, s32 arg2);
void EftHit_SetShapeSpheres(void *arg0, s32 arg1, s32 arg2);
void func_00127128(void *arg0);

void func_00168520(u8 *arg0) {
    u8 *temp_s3;
    u8 *temp_s4;
    u8 *temp_s0;
    s32 temp_a1;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s0_3;
    f32 temp_f0;
    f32 temp_f20;

    temp_s3 = *(u8 **)(arg0 + 0x38);
    temp_s4 = EftHit_GetNew();
    temp_f0 = func_00152958(temp_s3 + 0x124);
    *(s64 *)(temp_s4 + 0x10) = *(s64 *)(temp_s3 + 0xE0);
    temp_a1 = *(s32 *)(temp_s4 + 0x50) | 0x4A;
    *(s64 *)(temp_s4 + 0x18) = *(s64 *)(temp_s3 + 0xE8);
    *(s64 *)(temp_s4 + 0x20) = *(s64 *)(temp_s3 + 0xF0);
    *(s64 *)(temp_s4 + 0x28) = *(s64 *)(temp_s3 + 0xF8);
    *(s64 *)(temp_s4 + 0x30) = *(s64 *)(temp_s3 + 0x100);
    *(s64 *)(temp_s4 + 0x38) = *(s64 *)(temp_s3 + 0x108);
    *(s64 *)(temp_s4 + 0x40) = *(s64 *)(temp_s3 + 0x110);
    *(u8 **)(temp_s4 + 0x60) = arg0;
    *(s64 *)(temp_s4 + 0x48) = *(s64 *)(temp_s3 + 0x118);
    temp_a0 = *(s32 *)(temp_s3 + 0x120);
    *(s32 *)(temp_s4 + 0x50) = temp_a1;
    *(s32 *)(temp_s4 + 0x64) = temp_a0;
    temp_v0 = *(s32 *)(*(u8 **)(*(u8 **)(temp_s3 + 0x120) + 0x20) + 0x1C);
    temp_f20 = *(f32 *)(temp_s3 + 0x24) * temp_f0;

    if (temp_v0 != 0) {
        temp_s0 = temp_s3 + 0xC0;
        temp_s2 = EftHitArena_AllocBox(temp_a0, temp_a1, 1);
        temp_s1 = EftHitArena_AllocBox();
        ColCapsule_Set(temp_f20, temp_s2, temp_s0, temp_s3 + 0xF0);
        ColCapsule_Set(temp_f20, temp_s1, temp_s0, temp_s3 + 0x100);
        EftHit_SetShapeBoxes(temp_s4, temp_s2, temp_s1);
    } else {
        temp_s1 = func_00127F88(temp_a0, temp_a1, 1);
        temp_s0_3 = func_00127F88();
        ColSphere_Set(temp_f20, temp_s1, temp_s3 + 0xF0);
        ColSphere_Set(temp_f20, temp_s0_3, temp_s3 + 0x100);
        EftHit_SetShapeSpheres(temp_s4, temp_s1, temp_s0_3);
    }
    func_00127128(temp_s4);
}
