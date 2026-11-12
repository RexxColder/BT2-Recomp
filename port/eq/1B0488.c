#include "common.h"

void ColCapsule_Set(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
s32 EftHitArena_AllocBox();
s32 EftHit_GetNew(void);
void EftHit_SetShapeBoxes(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);

void func_001B0488(s32 arg0) {
    f32 f20;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 v0;

    v0 = EftHit_GetNew();
    s1 = v0;
    s0 = *(s32 *)(arg0 + 0x38);
    v0 = s0 + 0x180;
    s4 = s0 + 0x10;
    *(f32 *)(s1 + 0x10) = *(f32 *)(s0 + 0x0);
    *(f32 *)(s1 + 0x14) = *(f32 *)(s0 + 0x4);
    *(f32 *)(s1 + 0x18) = *(f32 *)(s0 + 0x8);
    *(f32 *)(s1 + 0x1C) = *(f32 *)(s0 + 0xC);
    *(f32 *)(s1 + 0x20) = *(f32 *)(s0 + 0x0);
    *(f32 *)(s1 + 0x24) = *(f32 *)(s0 + 0x4);
    *(f32 *)(s1 + 0x28) = *(f32 *)(s0 + 0x8);
    *(f32 *)(s1 + 0x2C) = *(f32 *)(s0 + 0xC);
    *(f32 *)(s1 + 0x30) = *(f32 *)(s0 + 0x10);
    *(f32 *)(s1 + 0x34) = *(f32 *)(s0 + 0x14);
    *(f32 *)(s1 + 0x38) = *(f32 *)(s0 + 0x18);
    *(s32 *)(s1 + 0x60) = arg0;
    *(f32 *)(s1 + 0x3C) = *(f32 *)(s0 + 0x1C);
    *(s32 *)(s1 + 0x54) = 0;
    *(s32 *)(s1 + 0x68) = v0;
    f20 = *(f32 *)(v0 + 0x28);
    s3 = EftHitArena_AllocBox();
    s2 = EftHitArena_AllocBox();
    ColCapsule_Set(f20, s3, s4, s0);
    ColCapsule_Set(f20, s2, s0 + 0x20, s4);
    EftHit_SetShapeBoxes(s1, s3, s2);
    func_00127128(s1);
}
