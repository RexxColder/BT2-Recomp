#include "common.h"

void ColCapsule_Set(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
s32 EftHitArena_AllocBox();
s32 EftHit_GetNew(void);
void EftHit_SetShapeBoxes(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);
f32 func_00152958(s32 arg0);

void func_00159B80(s32 arg0) {
    f32 f20;
    s32 a0;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;

    s0 = *(s32 *)(arg0 + 0x38);
    s1 = EftHit_GetNew();
    s4 = s0 + 0x40;
    f20 = *(f32 *)(s0 + 0x14) * func_00152958(s0 + 0xA4);
    *(s64 *)(s1 + 0x10) = *(s64 *)(s0 + 0x60);
    a0 = *(s32 *)(s1 + 0x50) | 0x40;
    f20 = f20 * 1.5f;
    *(s64 *)(s1 + 0x18) = *(s64 *)(s0 + 0x68);
    *(s64 *)(s1 + 0x20) = *(s64 *)(s0 + 0x70);
    *(s64 *)(s1 + 0x28) = *(s64 *)(s0 + 0x78);
    *(s64 *)(s1 + 0x30) = *(s64 *)(s0 + 0x80);
    *(s64 *)(s1 + 0x38) = *(s64 *)(s0 + 0x88);
    *(s64 *)(s1 + 0x40) = *(s64 *)(s0 + 0x90);
    *(s32 *)(s1 + 0x60) = arg0;
    *(s64 *)(s1 + 0x48) = *(s64 *)(s0 + 0x98);
    *(s32 *)(s1 + 0x50) = a0;
    *(s32 *)(s1 + 0x64) = *(s32 *)(s0 + 0xA0);
    s3 = EftHitArena_AllocBox(a0);
    s2 = EftHitArena_AllocBox();
    ColCapsule_Set(f20, s3, s4, s0 + 0x70);
    ColCapsule_Set(f20, s2, s4, s0 + 0x80);
    EftHit_SetShapeBoxes(s1, s3, s2);
    func_00127128(s1);
}
