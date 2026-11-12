#include "common.h"

void *EftHit_GetNew(void);
f32 func_00152958(void *arg0);
void ColCapsule_Set(f32 farg0, s32 arg0, void *arg1, void *arg2);
void ColSphere_Set(f32 farg0, s32 arg0, void *arg1);
s32 EftHitArena_AllocBox();
void EftHit_SetShapeBoxes(void *arg0, s32 arg1, s32 arg2);
void EftHit_SetShapeSpheres(void *arg0, s32 arg1, s32 arg2);
s32 func_00127F88();
void func_00127128(void *arg0);

void func_001603A8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f20;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s64 temp_a0;
    u8 *temp_s3;
    u8 *temp_s4;

    temp_s3 = *(u8 **)(arg0 + 0x38);
    temp_s4 = (u8 *)EftHit_GetNew();
    temp_f0 = func_00152958(temp_s3 + 0x104);
    *(s64 *)(temp_s4 + 0x10) = *(s64 *)(temp_s3 + 0xC0);
    *(s64 *)(temp_s4 + 0x18) = *(s64 *)(temp_s3 + 0xC8);
    *(s64 *)(temp_s4 + 0x20) = *(s64 *)(temp_s3 + 0xD0);
    *(s64 *)(temp_s4 + 0x28) = *(s64 *)(temp_s3 + 0xD8);
    *(s64 *)(temp_s4 + 0x30) = *(s64 *)(temp_s3 + 0xE0);
    *(s64 *)(temp_s4 + 0x38) = *(s64 *)(temp_s3 + 0xE8);
    *(s64 *)(temp_s4 + 0x40) = *(s64 *)(temp_s3 + 0xF0);
    temp_a0 = *(s64 *)(temp_s3 + 0xF8);
    *(u8 **)(temp_s4 + 0x60) = arg0;
    *(s64 *)(temp_s4 + 0x48) = temp_a0;
    *(u8 **)(temp_s4 + 0x64) = *(u8 **)(temp_s3 + 0x100);
    temp_v0 = *(s32 *)(*(u8 **)(*(u8 **)(temp_s3 + 0x100) + 0x20) + 0x1C);
    temp_f20 = *(f32 *)(temp_s3 + 0x20) * temp_f0;
    if (temp_v0 == 0) {
        temp_s1 = func_00127F88(temp_a0, 1);
        temp_s0 = func_00127F88();
        ColSphere_Set(temp_f20, temp_s1, temp_s3 + 0xD0);
        ColSphere_Set(temp_f20, temp_s0, temp_s3 + 0xE0);
        EftHit_SetShapeSpheres(temp_s4, temp_s1, temp_s0);
    } else {
        temp_s2 = EftHitArena_AllocBox(temp_a0, 1);
        temp_s1 = EftHitArena_AllocBox();
        ColCapsule_Set(temp_f20, temp_s2, temp_s3 + 0xA0, temp_s3 + 0xD0);
        ColCapsule_Set(temp_f20, temp_s1, temp_s3 + 0xA0, temp_s3 + 0xE0);
        EftHit_SetShapeBoxes(temp_s4, temp_s2, temp_s1);
    }
    func_00127128(temp_s4);
}
