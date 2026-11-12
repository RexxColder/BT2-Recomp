#include "common.h"

f32 sinf(f32 x);
f32 cosf(f32 x);
f32 atanf(f32 x);
void Mtx_InverseRT(void *a0, void *a1);
void func_00129C28(void *a0, void *a1);
void func_00129C50(void *a0, void *a1, void *a2);
f32 func_00129CD8(void *a0, void *a1);
extern void *gBtlCamView;
extern f32 D_00384178;
extern f32 D_0038417C;
extern u8 D_003886C0[] __attribute__((section(".data")));

void func_0012B9C0(void) {
    f32 sp[20];
    u8 *s0;
    u8 *s1;
    s32 s3;
    f32 f21;
    f32 f20;
    f32 f23;
    f32 f22;
    f32 f2;

    f21 = D_00384178;
    s0 = D_003886C0;
    s1 = s0;
    f23 = sinf(f21);
    f2 = cosf(f21);
    f20 = f2 * 0.75f;
    *(f32 *)(s0 + 0x4) = f2;
    *(f32 *)(s0 + 0x8) = f23;
    *(f32 *)(s0 + 0x18) = f23;
    *(s32 *)(s0 + 0x0) = 0;
    *(s32 *)(s0 + 0x10) = 0;
    f22 = 1.0f;
    *(f32 *)(s0 + 0xC) = f22;
    *(f32 *)(s0 + 0x14) = -f2;
    *(f32 *)(s0 + 0x1C) = f22;
    f20 = atanf(f23 / f20);
    f23 = sinf(f20);
    f2 = cosf(f20);
    *(f32 *)(s0 + 0x20) = -f2;
    *(s32 *)(s0 + 0x24) = 0;
    *(f32 *)(s0 + 0x28) = f23;
    *(f32 *)(s0 + 0x2C) = f22;
    *(f32 *)(s0 + 0x30) = f2;
    *(s32 *)(s0 + 0x34) = 0;
    *(f32 *)(s0 + 0x38) = f23;
    *(f32 *)(s0 + 0x3C) = f22;
    *(s32 *)(s0 + 0x40) = 0;
    *(s32 *)(s0 + 0x44) = 0;
    *(f32 *)(s0 + 0x48) = f22;
    *(f32 *)(s0 + 0x4C) = -f22;
    Mtx_InverseRT(sp, gBtlCamView);
    func_00129C28(&sp[16], &sp[12]);
    sp[12] = 0.0f;
    sp[14] = 0.0f;
    sp[13] = 0.0f;
    s3 = 4;
    do {
        func_00129C50(s1, sp, s1);
        s3 -= 1;
        *(f32 *)(s1 + 0xC) = -func_00129CD8(s1, &sp[16]);
        s1 += 0x10;
    } while (s3 >= 0);
    *(f32 *)(s0 + 0x4C) = *(f32 *)(s0 + 0x4C) - D_0038417C;
}
