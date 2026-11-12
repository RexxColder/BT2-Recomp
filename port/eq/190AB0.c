#include "common.h"

s32 EftHit_GetNew(s32 arg0);
f32 func_00152958(s32 arg0);
s32 EftHitArena_AllocBox();
s32 func_00127F88();
void ColCapsule_Set(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
void EftHit_SetShapeBoxes(s32 arg0, s32 arg1, s32 arg2);
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);

void func_00190AB0(u8 *arg0) {
    u8 *s3;
    s32 s4;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 temp_v0;
    f32 f0;
    f32 f20;

    s3 = (u8 *)*(s32 *)(arg0 + 0x38);
    s4 = EftHit_GetNew((s32)arg0);
    s1 = *(s32 *)s3;
    f0 = func_00152958((s32)(s3 + 0x60));

    *(s64 *)(s4 + 0x10) = *(s64 *)(s3 + 0x810);
    *(s64 *)(s4 + 0x18) = *(s64 *)(s3 + 0x818);
    *(s64 *)(s4 + 0x20) = *(s64 *)(s3 + 0x820);
    *(s64 *)(s4 + 0x28) = *(s64 *)(s3 + 0x828);
    *(s64 *)(s4 + 0x30) = *(s64 *)(s3 + 0x830);
    *(s64 *)(s4 + 0x38) = *(s64 *)(s3 + 0x838);
    *(s64 *)(s4 + 0x40) = *(s64 *)(s3 + 0x840);
    *(s32 *)(s4 + 0x60) = (s32)arg0;
    *(s64 *)(s4 + 0x48) = *(s64 *)(s3 + 0x848);
    *(s32 *)(s4 + 0x64) = s1;

    f20 = *(f32 *)(s3 + 0x38) * f0;

    if (*(s32 *)(s3 + 0x30) & 0x100) {
        *(s32 *)(s4 + 0x50) = *(s32 *)(s4 + 0x50) | 0x80;
    }
    if (*(s32 *)(s3 + 0x30) & 0x800) {
        *(s32 *)(s4 + 0x50) = *(s32 *)(s4 + 0x50) | 0x10;
    }

    temp_v0 = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x1C);
    if (temp_v0 == 0) {
        s1 = func_00127F88(1);
        s0 = func_00127F88();
        ColSphere_Set(f20, s1, (s32)(s3 + 0x820));
        ColSphere_Set(f20, s0, (s32)(s3 + 0x830));
        EftHit_SetShapeSpheres(s4, s1, s0);
    } else {
        s0 = (s32)(s3 + 0x810);
        s2 = EftHitArena_AllocBox(1);
        s1 = EftHitArena_AllocBox();
        ColCapsule_Set(f20, s2, s0, (s32)(s3 + 0x820));
        ColCapsule_Set(f20, s1, s0, (s32)(s3 + 0x830));
        EftHit_SetShapeBoxes(s4, s2, s1);
    }
    func_00127128(s4);
}
