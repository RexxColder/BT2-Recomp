#include "common.h"

void ColCapsule_Set(f32 farg0, s32 arg1, s32 arg2, s32 arg3);
s32 EftHitArena_AllocBox(void);
u8 *EftHit_GetNew(void);
void EftHit_SetShapeBoxes(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);
f32 func_00152958(s32 arg0);

void func_0019D240(u8 *arg0) {
    u8 *s2;
    u8 *s3;
    u8 *s4;
    s32 s0;
    s32 s1;
    f32 f20;

    s2 = *(u8 **)(arg0 + 0x38);
    s3 = EftHit_GetNew();
    s4 = s2 + 0xB50;
    if (*(s32 *)(s2 + 4) != 0) {
        f20 = func_00152958((s32)(s2 + 0x90));
        *(s64 *)(s3 + 0x10) = *(s64 *)(s2 + 0xB30);
        *(s64 *)(s3 + 0x18) = *(s64 *)(s2 + 0xB38);
        *(s64 *)(s3 + 0x20) = *(s64 *)(s2 + 0xB40);
        *(s64 *)(s3 + 0x28) = *(s64 *)(s2 + 0xB48);
        *(s64 *)(s3 + 0x30) = *(s64 *)(s2 + 0xB50);
        *(s64 *)(s3 + 0x38) = *(s64 *)(s2 + 0xB58);
        *(s64 *)(s3 + 0x40) = *(s64 *)(s2 + 0xB60);
        *(u8 **)(s3 + 0x60) = arg0;
        *(s64 *)(s3 + 0x48) = *(s64 *)(s2 + 0xB68);
        *(s32 *)(s3 + 0x64) = *(s32 *)(s2 + 4);
        f20 = *(f32 *)(s2 + 0xBF8) * f20;
        if (*(u16 *)(s2 + 0xC24) & 0x100) {
            *(s32 *)(s3 + 0x50) = *(s32 *)(s3 + 0x50) | 0x10;
        }
        s1 = EftHitArena_AllocBox();
        s0 = EftHitArena_AllocBox();
        ColCapsule_Set(f20, s1, (s32)s4, (s32)(s2 + 0xB40));
        ColCapsule_Set(f20, s0, (s32)(s2 + 0xB70), (s32)s4);
        EftHit_SetShapeBoxes((s32)s3, s1, s0);
        func_00127128((s32)s3);
    }
}
