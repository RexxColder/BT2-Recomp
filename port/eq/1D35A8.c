#include "common.h"

extern u8 D_0036F0A0[];
extern u8 D_00342F40[];
extern u8 D_00342ED0[];
extern f32 D_0038549C;
extern s32 D_00387E9C;

s32 func_001D3028(void);
f32 func_0012A3F8(f32 farg0);
f32 Mathf_Cos(f32 farg0);
s32 rand(void);
void func_00129C28(s32 arg0, s32 arg1);

/* Spawns one particle: origin from arg0 (16 bytes), two random angles, colour/alpha from the
   float args, and a table-driven per-particle frame (arg3 < 0 uses the fixed frame). */
s32 func_001D35A8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3,
                  f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                  f32 farg8, f32 farg9) {
    f32 v54[4];
    f32 v56[4];
    u8 v57[16];
    u8 *pp;
    u8 *gs;
    s32 result;
    s32 r1;
    s32 r2;
    f32 th1;
    f32 th2;
    f32 s1f;
    f32 s2f;
    f32 c2;

    __builtin_memcpy(v54, arg0, 16);
    v56[0] = 128.0f;
    v56[1] = 128.0f;
    v56[2] = 128.0f;
    v56[3] = (f32)arg2;
    __builtin_memcpy(v57, D_0036F0A0, 16);

    result = func_001D3028();
    pp = (u8 *)result;
    if (pp != 0) {
        *(f32 *)(pp + 0x20) = v54[0];
        *(f32 *)(pp + 0x24) = v54[1];
        *(f32 *)(pp + 0x28) = v54[2];
        *(f32 *)(pp + 0x68) = farg0;

        r1 = rand();
        th1 = ((f32)(r1 % 360) / 180.0f) * D_0038549C;
        s1f = func_0012A3F8(th1);
        *(f32 *)(pp + 0x18) = Mathf_Cos(th1);
        r2 = rand();
        th2 = ((f32)(r2 % 360) / 180.0f) * D_0038549C;
        c2 = Mathf_Cos(th2);
        *(f32 *)(pp + 0x10) = c2 * s1f;
        s2f = func_0012A3F8(th2);
        *(f32 *)(pp + 0x14) = (s2f * s1f) * farg0;
        *(f32 *)(pp + 0x10) = *(f32 *)(pp + 0x10) * farg0;
        *(f32 *)(pp + 0x18) = *(f32 *)(pp + 0x18) * farg0;

        *(f32 *)(pp + 0x64) = farg7;
        *(f32 *)(pp + 0x6C) = farg1;
        *(f32 *)(pp + 0x70) = farg2;
        *(f32 *)(pp + 0x74) = farg3;
        *(f32 *)(pp + 0x78) = farg4;
        *(f32 *)(pp + 0x7C) = farg5;
        *(f32 *)(pp + 0x60) = farg6;
        *(f32 *)(pp + 0x84) = 1.0f / (farg8 * 30.0f);
        *(f32 *)(pp + 0x80) = 1.0f;

        *(s32 *)(pp + 0x94) = arg3;
        if (arg3 < 0) {
            pp[0x90] = 11;
            pp[0x91] = 0;
            func_00129C28((s32)(pp + 0x30), (s32)v56);
            func_00129C28((s32)(pp + 0x40), (s32)v56);
            func_00129C28((s32)(pp + 0x50), (s32)v57);
        } else {
            pp[0x90] = (u8)(pp[0x94] + 1);
            pp[0x91] = 1;
            func_00129C28((s32)(pp + 0x30), (s32)(D_00342F40 + 16 * arg3));
            func_00129C28((s32)(pp + 0x40), (s32)(D_00342F40 + 16 * *(s32 *)(pp + 0x94)));
            func_00129C28((s32)(pp + 0x50), (s32)(D_00342ED0 + 16 * *(s32 *)(pp + 0x94)));
        }

        pp[0x93] = (u8)arg1;
        *(f32 *)(pp + 0x8C) = farg9;
        pp[0x99] = 1;
        *(s32 *)(pp + 0x88) = 0;
        pp[0x92] = 0;
        pp[0x98] = 0;

        gs = (u8 *)D_00387E9C;
        *(s32 *)(gs + 0x1424) = *(s32 *)(gs + 0x1424) + 1;
        result = *(s32 *)(gs + 0x1424);
    }
    return result;
}
