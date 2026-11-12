#include "common.h"

extern u8 *D_00388714 __attribute__((section(".data")));
extern f32 D_00384238;
extern f32 D_0038423C;
extern f32 D_00384240;
extern f32 D_00384244;
extern f32 D_00384248;
extern f32 D_0038424C;
extern f32 D_00384250;
extern f32 D_00387728;
extern u8 *gEftBurst;

void EftBurst_InitDebris(u8 *arg0);
void func_00133670(s32 arg0);
void func_00133E28(s32 arg0);
s32 rand(void);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
void func_003126C8(void *arg0, void *arg1);
void func_00312680(f32 farg0, void *arg0, void *arg1);

void func_00132F18(u8 *arg0) {
    f32 sp[8];
    u8 *s1;
    u8 *v3;
    s32 r;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f2;
    f32 f0;
    f32 f26;
    f32 f24;

    s1 = arg0 + 0x20;
    EftBurst_InitDebris(arg0);
    *(s32 *)(arg0 + 0x50) = 0xF2;
    f26 = D_00384238;
    f24 = D_0038423C;
    *(s32 *)(arg0 + 0x48) = *(s32 *)(D_00388714 + 0x10) + 0xC0;
    r = (rand() & 0xF) + 7;
    *(s32 *)(arg0 + 0x44) = r;
    *(s32 *)(arg0 + 0x40) = r;
    *(f32 *)(arg0 + 0x4C) = ((f32)(rand() & 0x1F) * 0.03125f) + 2.5f;

    v3 = arg0 + 0x30;
    *(s32 *)(v3 + 0xC) = 0;
    *(s32 *)(v3 + 0x0) = 0;
    *(s32 *)(v3 + 0x4) = 0;
    *(s32 *)(v3 + 0x8) = 0;
    *(s32 *)(arg0 + 0x20) = 0;
    *(f32 *)(s1 + 0x4) = f26;
    *(s32 *)(s1 + 0x8) = 0;
    *(s32 *)(s1 + 0xC) = 0;

    f21 = (f32)*(s32 *)(gEftBurst + 0x4) * D_00384240;
    f22 = (D_00387728 * f24) / 180.0f;
    if (f21 > 1.0f) {
        f21 = 1.0f;
    }
    f20 = ((f32)(rand() & 0x1F) * 0.03125f * (f21 + 2.0f)) + 10.0f;

    sp[4] = cosf(f22) * f20;
    sp[5] = sinf(f22) * f20;
    sp[6] = -50.0f;
    sp[7] = 0.0f;
    sp[0] = sp[4];
    sp[1] = sp[5];
    sp[2] = sp[6];
    sp[3] = sp[7];
    func_003126C8(arg0, sp);
    func_00312680(D_00384244, sp, sp);

    sp[2] = ((f32)(rand() & 0x1F) / 15.0f) * D_00384248 + f21 * D_0038424C;
    func_003126C8(arg0 + 0x10, sp);

    *(f32 *)(s1 + 0x4) = f26;
    *(f32 *)(s1 + 0x0) = D_00384250;
    *(s32 *)(s1 + 0xC) = 0;
    *(f32 *)(s1 + 0x8) = f22;

    if (rand() & 1) {
        *(s32 *)(arg0 + 0x5C) = 0x30;
        *(s32 *)(arg0 + 0x60) = 0x40;
        *(s32 *)(arg0 + 0x50) = *(s32 *)(arg0 + 0x50) | 8;
    } else {
        *(s32 *)(arg0 + 0x60) = 0x40;
        *(s32 *)(arg0 + 0x5C) = 0x40;
    }

    f2 = D_00387728 + (f32)(rand() & 0x3F);
    f0 = f2;
    if (180.0f < f2) {
        f0 = f2 - 360.0f;
    }
    D_00387728 = f0;
    *(void **)(arg0 + 0x58) = (void *)&func_00133E28;
    *(void **)(arg0 + 0x54) = (void *)&func_00133670;
}
