#include "common.h"

s32 EftHit_GetNew(s32 arg0);
f32 func_00152958(s32 arg0);
void ColCapsule_Set(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
s32 EftHitArena_AllocBox();
s32 func_00127F88();
void EftHit_SetShapeBoxes(s32 arg0, s32 arg1, s32 arg2);
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);

void func_0014A508(s32 arg0) {
    f32 temp_f0;
    f32 temp_f20;
    s32 temp_s0;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s1_3;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0;
    s64 temp_a0;

    temp_s3 = *(s32 *)(arg0 + 0x38);
    temp_s4 = EftHit_GetNew(arg0);
    temp_f0 = func_00152958(temp_s3 + 0xB4);
    *(s64 *)(temp_s4 + 0x10) = *(s64 *)(temp_s3 + 0x70);
    *(s64 *)(temp_s4 + 0x18) = *(s64 *)(temp_s3 + 0x78);
    *(s64 *)(temp_s4 + 0x20) = *(s64 *)(temp_s3 + 0x80);
    *(s64 *)(temp_s4 + 0x28) = *(s64 *)(temp_s3 + 0x88);
    *(s64 *)(temp_s4 + 0x30) = *(s64 *)(temp_s3 + 0x90);
    *(s64 *)(temp_s4 + 0x38) = *(s64 *)(temp_s3 + 0x98);
    *(s64 *)(temp_s4 + 0x40) = *(s64 *)(temp_s3 + 0xA0);
    temp_a0 = *(s64 *)(temp_s3 + 0xA8);
    *(s32 *)(temp_s4 + 0x60) = arg0;
    *(s64 *)(temp_s4 + 0x48) = temp_a0;
    *(s32 *)(temp_s4 + 0x64) = *(s32 *)(temp_s3 + 0xB0);
    temp_v0 = *(s32 *)(*(s32 *)(*(s32 *)(temp_s3 + 0xB0) + 0x20) + 0x1C);
    temp_f20 = *(f32 *)(temp_s3 + 0x18) * temp_f0;
    if (temp_v0 == 0) {
        temp_s1_3 = func_00127F88(temp_a0, 1);
        temp_s0_3 = func_00127F88();
        ColSphere_Set(temp_f20, temp_s1_3, temp_s3 + 0x80);
        ColSphere_Set(temp_f20, temp_s0_3, temp_s3 + 0x90);
        EftHit_SetShapeSpheres(temp_s4, temp_s1_3, temp_s0_3);
    } else {
        temp_s0 = temp_s3 + 0x50;
        temp_s2 = EftHitArena_AllocBox(temp_a0, 1);
        temp_s1 = EftHitArena_AllocBox();
        ColCapsule_Set(temp_f20, temp_s2, temp_s0, temp_s3 + 0x80);
        ColCapsule_Set(temp_f20, temp_s1, temp_s0, temp_s3 + 0x90);
        EftHit_SetShapeBoxes(temp_s4, temp_s2, temp_s1);
    }
    func_00127128(temp_s4);
}
