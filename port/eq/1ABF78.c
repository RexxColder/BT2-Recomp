#include "common.h"

s32 EftHit_GetNew(void);
void ColSphere_Set(s32 arg0, s32 arg1, f32 farg0);
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
s32 func_00127128(s32 arg0);
s32 func_00127F88();

s32 func_001ABF78(u8 *arg0) {
    u8 *s1;
    u8 *s0;
    s32 orig;
    s32 a1v;
    s32 a2v;
    s32 a0v;
    s32 s3;
    s32 s2;
    f32 f20;

    s1 = *(u8 **)(arg0 + 0x38);
    s0 = (u8 *)EftHit_GetNew();
    *(s32 *)(s0 + 0x60) = (s32)arg0;
    orig = *(s32 *)(s0 + 0x50);
    a1v = orig | 2;
    a2v = orig | 0x402;
    *(s64 *)(s0 + 0x10) = *(s64 *)(s1 + 0x40);
    *(s64 *)(s0 + 0x18) = *(s64 *)(s1 + 0x48);
    *(s64 *)(s0 + 0x20) = *(s64 *)(s1 + 0x50);
    *(s64 *)(s0 + 0x28) = *(s64 *)(s1 + 0x58);
    *(s64 *)(s0 + 0x30) = *(s64 *)(s1 + 0x60);
    *(s64 *)(s0 + 0x38) = *(s64 *)(s1 + 0x68);
    *(s64 *)(s0 + 0x40) = *(s64 *)(s1 + 0x70);
    *(s64 *)(s0 + 0x48) = *(s64 *)(s1 + 0x78);
    *(s32 *)(s0 + 0x54) = 0;
    *(s32 *)(s0 + 0x50) = a1v;
    *(u8 *)(s0 + 0x5C) = (u8)((*(s32 *)(s1 + 0xC0) >> 5) & 1);
    a0v = ((*(s32 *)(s1 + 0xC0) & 0x1000) == 0) ? a2v : (orig | 0x202);
    *(s32 *)(s0 + 0x50) = a0v;
    *(s32 *)(s0 + 0x68) = (s32)s1;
    *(s32 *)(s0 + 0x54) = (*(s32 *)(s1 + 0xC0) >> 9) & 1;
    f20 = *(f32 *)(s1 + 0xD4);
    s3 = func_00127F88(a0v, a1v, a2v);
    s2 = func_00127F88();
    ColSphere_Set(s3, (s32)(s1 + 0x50), f20);
    ColSphere_Set(s2, (s32)(s1 + 0x60), f20);
    EftHit_SetShapeSpheres((s32)s0, s3, s2);
    return func_00127128((s32)s0);
}
