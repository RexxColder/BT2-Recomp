#include "common.h"

s32 EftSteam_FindFreePart(s32 arg0);
void Mtx_InverseRT(s32 arg0, s32 arg1);
f32 Rand_FloatRange(f32 farg0, f32 farg1);
extern f32 D_003842FC;
void Vec3_Cross(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);

extern s32 gBtlCamView;
extern u8 D_0036DD10[] __attribute__((section(".data")));

void EftSteam_Emit(u8 *arg0) {
    u8 sp[0x70];
    u8 *s2;
    s32 s1;
    s32 v0;
    s32 q;
    f32 t;
    f32 r;

    s2 = (u8 *)EftSteam_FindFreePart((s32)(arg0 + 0x70));
    *(s64 *)(sp + 0x68) = *(s64 *)(D_0036DD10 + 8);
    *(s64 *)(sp + 0x60) = *(s64 *)(D_0036DD10 + 0);

    if (s2 != NULL) {
        s1 = (s32)(s2 + 0x10);
        Mtx_InverseRT((s32)sp, gBtlCamView);
        func_00129B58((s32)(sp + 0x40), (s32)(sp + 0x30), (s32)arg0);
        Vec3_Normalize((s32)(sp + 0x40), (s32)(sp + 0x40));
        Vec3_Cross((s32)(sp + 0x50), (s32)(sp + 0x60), (s32)(sp + 0x40));
        func_00129C28((s32)s2, (s32)arg0);

        r = Rand_FloatRange(-*(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0x40));
        *(f32 *)s2 = *(f32 *)s2 + *(f32 *)(sp + 0x50) * r;
        *(f32 *)(s2 + 0xC) = 1.0f;
        r = Rand_FloatRange(-*(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0x40));
        *(f32 *)(s2 + 0x8) = *(f32 *)(s2 + 0x8) + *(f32 *)(sp + 0x58) * r;

        r = Rand_FloatRange(-*(f32 *)(arg0 + 0x44), *(f32 *)(arg0 + 0x44));
        *(f32 *)(sp + 0x40) = *(f32 *)(sp + 0x40) * r;
        r = Rand_FloatRange(-*(f32 *)(arg0 + 0x44), *(f32 *)(arg0 + 0x44));
        *(f32 *)(sp + 0x48) = *(f32 *)(sp + 0x48) * r;
        Vec4_Set(s1, *(f32 *)(sp + 0x40), -1.0f, *(f32 *)(sp + 0x48), 1.0f);
        Vec3_Normalize(s1, s1);

        func_00129C28((s32)(s2 + 0x20), (s32)(arg0 + 0x20));
        *(f32 *)(s2 + 0x44) = *(f32 *)(arg0 + 0x34);
        r = Rand_FloatRange(-*(f32 *)(arg0 + 0x48), *(f32 *)(arg0 + 0x48));
        *(f32 *)(s2 + 0x40) = *(f32 *)(arg0 + 0x30) + r;
        r = Rand_FloatRange(-*(f32 *)(arg0 + 0x4C), *(f32 *)(arg0 + 0x4C));
        *(f32 *)(s2 + 0x48) = *(f32 *)(arg0 + 0x38) + r;

        v0 = *(s32 *)(arg0 + 0x50);
        r = Rand_FloatRange((f32)(-v0), (f32)v0);
        t = (f32)*(s32 *)(arg0 + 0x3C) + r;
        /* cvt.w.s truncates toward zero (saturating): plain cast */
        q = (s32)t;
        *(s32 *)(s2 + 0x50) = q;
        *(f32 *)(s2 + 0x4C) = Rand_FloatRange(0.0f, D_003842FC);

        func_00129BD0((s32)(s2 + 0x30), s1, *(f32 *)(s2 + 0x40));
        *(s32 *)(arg0 + 0xC74) = *(s32 *)(arg0 + 0xC74) + 1;
    }
}
