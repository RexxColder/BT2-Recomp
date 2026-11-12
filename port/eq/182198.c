#include "common.h"

u8 *EftHit_GetNew(u8 *arg0);
s32 EftHitArena_AllocBox();
s32 func_00127F88();
void ColCapsule_Set(f32 farg0, s32 arg0, u8 *arg1, u8 *arg2);
void ColSphere_Set(f32 farg0, s32 arg0, u8 *arg1);
void EftHit_SetShapeBoxes(u8 *arg0, s32 arg1, s32 arg2);
void EftHit_SetShapeSpheres(u8 *arg0, s32 arg1, s32 arg2);
void func_00127128(u8 *arg0);

void func_00182198(u8 *arg0) {
    u8 *hit;
    u8 *s0;
    u8 *a1;
    u8 *a2;
    s64 a0v;
    s32 v0;
    s32 r1;
    s32 r2;
    f32 f20;

    hit = EftHit_GetNew(arg0);
    s0 = *(u8 **)(arg0 + 0x38);
    a1 = s0 + 0xA00;
    f20 = *(f32 *)(s0 + 0xA88);
    a2 = *(u8 **)(a1 + 0x28);
    /* 8 raw s64 copies of a1+0x30..0x70 into hit+0x10..0x50 */
    *(s64 *)(hit + 0x10) = *(s64 *)(a1 + 0x30);
    *(s64 *)(hit + 0x18) = *(s64 *)(a1 + 0x38);
    *(s64 *)(hit + 0x20) = *(s64 *)(a1 + 0x40);
    *(s64 *)(hit + 0x28) = *(s64 *)(a1 + 0x48);
    *(s64 *)(hit + 0x30) = *(s64 *)(a1 + 0x50);
    *(s64 *)(hit + 0x38) = *(s64 *)(a1 + 0x58);
    *(s64 *)(hit + 0x40) = *(s64 *)(a1 + 0x60);
    a0v = *(s64 *)(a1 + 0x68);
    *(s64 *)(hit + 0x48) = a0v;
    if (a1[0] & 4) {
        *(s32 *)(hit + 0x50) = *(s32 *)(hit + 0x50) | 0x10;
    }
    *(s32 *)(hit + 0x60) = (s32)arg0;
    *(s32 *)(hit + 0x64) = *(s32 *)(a1 + 0x28);
    v0 = *(s32 *)(*(u8 **)(a2 + 0x20) + 0x1C);

    if (v0 == 0) {
        r1 = func_00127F88(a0v, a1, a2, 1);
        r2 = func_00127F88();
        ColSphere_Set(f20, r1, hit + 0x20);
        ColSphere_Set(f20, r2, hit + 0x30);
        EftHit_SetShapeSpheres(hit, r1, r2);
    } else {
        r2 = EftHitArena_AllocBox(a0v, a1, a2, 1);
        r1 = EftHitArena_AllocBox();
        ColCapsule_Set(f20, r2, hit + 0x10, hit + 0x20);
        ColCapsule_Set(f20, r1, hit + 0x10, hit + 0x30);
        EftHit_SetShapeBoxes(hit, r2, r1);
    }
    func_00127128(hit);
}
