#include "common.h"

void *EftHit_GetNew(void);
void *EftHitArena_AllocBox(void);
f32 func_00152958(void *a0);
void ColCapsule_Set(void *cap, void *a, void *b, f32 radius);
void ColSphere_Set(void *sph, void *pos, f32 radius);
void EftHit_SetShapeSpheres(void *rec, void *a, void *b);
void EftHit_SetShapeBoxes(void *rec, void *a, void *b);
void *func_00127F88(void);
void func_00127128(void *arg0);

void func_001676A8(u8 *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *p;
    u8 *q;
    f32 f1;
    f32 f20;
    f32 scale;
    s32 r;

    s3 = *(u8 **)(arg0 + 0x38);
    s4 = EftHit_GetNew();
    scale = func_00152958(s3 + 0xB4);
    f1 = *(f32 *)(s3 + 0x1C);

    *(s64 *)(s4 + 0x10) = *(s64 *)(s3 + 0x70);
    *(s64 *)(s4 + 0x18) = *(s64 *)(s3 + 0x78);
    *(s64 *)(s4 + 0x20) = *(s64 *)(s3 + 0x80);
    *(s64 *)(s4 + 0x28) = *(s64 *)(s3 + 0x88);
    *(s64 *)(s4 + 0x30) = *(s64 *)(s3 + 0x90);
    *(s64 *)(s4 + 0x38) = *(s64 *)(s3 + 0x98);
    *(s64 *)(s4 + 0x40) = *(s64 *)(s3 + 0xA0);
    *(s64 *)(s4 + 0x48) = *(s64 *)(s3 + 0xA8);
    *(u8 **)(s4 + 0x60) = arg0;
    *(u8 **)(s4 + 0x64) = *(u8 **)(s3 + 0xB0);

    p = *(u8 **)(s3 + 0xB0);
    q = *(u8 **)(p + 0x20);
    r = *(s32 *)(q + 0x1C);
    f20 = f1 * scale;

    if (r == 0) {
        s1 = func_00127F88();
        s0 = func_00127F88();
        ColSphere_Set(s1, s3 + 0x80, f20);
        ColSphere_Set(s0, s3 + 0x90, f20);
        EftHit_SetShapeSpheres(s4, s1, s0);
    } else {
        s0 = s3 + 0x50;
        s2 = EftHitArena_AllocBox();
        s1 = EftHitArena_AllocBox();
        ColCapsule_Set(s2, s0, s3 + 0x80, f20);
        ColCapsule_Set(s1, s0, s3 + 0x90, f20);
        EftHit_SetShapeBoxes(s4, s2, s1);
    }
    func_00127128(s4);
}
