#include "common.h"

s32 EftWater_GetSurfaceY(void *arg0);
f32 StgAmb_Falloff(f32 arg0, f32 arg1, f32 arg2);
f32 Vec3_Dist(void *arg0, void *arg1);
void func_00276FD0(f32 arg0, void *arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_003126C8(void *arg0, void *arg1);
void sceVu0InversMatrix(void *arg0, void *arg1);
s32 rand(void);

extern u8 D_00376B60[] __attribute__((section(".data")));
extern u8 D_00376BE0[] __attribute__((section(".data")));
extern f32 D_0038704C;
extern f32 D_00387050;
extern f32 D_00387054;
extern f32 D_00387058;
extern f32 D_0038705C;
extern f32 D_00387060;
extern u8 *D_003876A0;
extern f32 D_00387AC8 __attribute__((section(".data")));
extern u8 D_00388D68[] __attribute__((section(".data")));
extern void *gBtlCamView;

void func_00277460(void) {
    u8 sp[0x120];
    f32 f20;
    f32 f21;
    f32 f0;
    s32 cnt;
    s32 r;
    s32 s0;
    s32 s1;
    s32 surf;
    s32 i;
    f32 xv;
    s32 ti;
    f32 fr;
    f32 d;
    u8 *a0p;
    u8 *sp0;

    f20 = 1.0f;
    cnt = *(s32 *)(D_00388D68 + 0xC);
    if (cnt == 0) {
        cnt = (rand() % 90) + 0x5A;
        *(s32 *)(D_00388D68 + 0xC) = cnt;
    }
    cnt = cnt - 1;
    *(s32 *)(D_00388D68 + 0xC) = cnt;
    if (cnt <= 0) {
        r = (rand() % 90) + 0x5A;
        *(s32 *)(D_00388D68 + 0xC) = r;
        r = rand();
        xv = ((f32)r / D_0038704C) * 62.0f;
        ti = (s32)xv;
        fr = xv - (f32)ti;
        if (xv >= 0.0f) {
            if (fr > 0.5f || (fr == 0.5f && (ti & 1))) {
                ti += 1;
            }
        } else {
            if (fr < -0.5f || (fr == -0.5f && (ti & 1))) {
                ti -= 1;
            }
        }
        s0 = ti;
        r = rand();
        func_00297FE0(2, 0xA, (s0 + 0x3F) >> 2, r % 127, 0);
    }

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) != 0) {
        func_00276FD0(0.25f, gBtlCamView);
        return;
    }

    sceVu0InversMatrix(sp, gBtlCamView);
    surf = EftWater_GetSurfaceY(sp + 0x110);
    if (surf == 0) {
        for (i = 0; i < 0x80; i++) {
            sp[0x40 + i] = D_00376BE0[i];
        }
        sceVu0InversMatrix(sp + 0xD0, gBtlCamView);
        f20 = D_00387AC8;
        func_003126C8(sp + 0xC0, sp + 0x100);
        *(s32 *)(sp + 0xC4) = 0;
        a0p = sp + 0x40;
        sp0 = sp + 0x40;
        s1 = 7;
        do {
            sp0 += 0x10;
            d = Vec3_Dist(a0p, sp + 0xC0);
            if (d < f20) {
                f20 = d;
            }
            s1 -= 1;
            a0p = sp0;
        } while (s1 >= 0);
        f20 = StgAmb_Falloff(f20, 280.0f, D_0038705C);
        func_00276FD0(f20 * D_00387060, 0);
        return;
    }

    if (*(f32 *)(sp + 0x34) < *(f32 *)(sp + 0x110)) {
        f21 = StgAmb_Falloff(-*(f32 *)(sp + 0x34) + *(f32 *)(sp + 0x110), 20.0f, 150.0f);
    } else {
        f21 = StgAmb_Falloff(*(f32 *)(sp + 0x34) - *(f32 *)(sp + 0x110), 0.0f, 10.0f);
    }
    f0 = D_00387050;
    f21 = f21 * f0;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) != 0) {
        func_00276FD0(0.25f, 0);
    } else {
        for (i = 0; i < 0x80; i++) {
            sp[0x40 + i] = D_00376B60[i];
        }
        f20 = D_00387AC8;
        func_003126C8(sp + 0xC0, sp + 0x30);
        *(s32 *)(sp + 0xC4) = 0;
        a0p = sp + 0x40;
        sp0 = sp + 0x40;
        s1 = 7;
        do {
            sp0 += 0x10;
            d = Vec3_Dist(a0p, sp + 0xC0);
            if (d < f20) {
                f20 = d;
            }
            s1 -= 1;
            a0p = sp0;
        } while (s1 >= 0);
        f20 = StgAmb_Falloff(f20, 280.0f, D_00387054);
    }
    func_00276FD0((f20 + f21) * 0.5f * D_00387058, 0);
}
