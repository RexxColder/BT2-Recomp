#include "common.h"

void ColCapsule_Set(f32 farg0, s32 arg1, s32 arg2, s32 arg3);
s32 EftHitArena_AllocBox();
void *EftHit_GetNew(void);
void EftHit_SetShapeBoxes(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);

void func_0019D0F8(u8 *arg0) {
    u8 *s3;
    u8 *s2;
    u8 *s4;
    u8 *a0v;
    s32 s0;
    s32 s1;
    f32 f20;

    s3 = *(u8 **)(arg0 + 0x38);
    s2 = (u8 *)EftHit_GetNew();
    a0v = s3 + 0x10;
    s4 = s3 + 0xB50;

    if (*(u8 *)(a0v + 0x35) != 0) {
        *(s64 *)(s2 + 0x10) = *(s64 *)(s3 + 0xB30);
        *(s64 *)(s2 + 0x18) = *(s64 *)(s3 + 0xB38);
        *(s64 *)(s2 + 0x20) = *(s64 *)(s3 + 0xB40);
        *(s64 *)(s2 + 0x28) = *(s64 *)(s3 + 0xB48);
        *(s64 *)(s2 + 0x30) = *(s64 *)(s3 + 0xB50);
        *(s64 *)(s2 + 0x38) = *(s64 *)(s3 + 0xB58);
        *(s64 *)(s2 + 0x40) = *(s64 *)(s3 + 0xB60);
        *(s32 *)(s2 + 0x60) = (s32)arg0;
        *(s64 *)(s2 + 0x48) = *(s64 *)(s3 + 0xB68);
        *(s32 *)(s2 + 0x68) = (s32)a0v;
        *(s32 *)(s2 + 0x54) = 0;
        if (*(u16 *)(s3 + 0xC24) & 0x100) {
            *(s32 *)(s2 + 0x50) = *(s32 *)(s2 + 0x50) | 0x10;
        }
        f20 = *(f32 *)(s3 + 0xBF8);
        s1 = EftHitArena_AllocBox((s32)a0v);
        s0 = EftHitArena_AllocBox();
        ColCapsule_Set(f20, s1, (s32)s4, (s32)(s3 + 0xB40));
        ColCapsule_Set(f20, s0, (s32)(s3 + 0xB70), (s32)s4);
        EftHit_SetShapeBoxes((s32)s2, s1, s0);
        func_00127128((s32)s2);
    }
}
