#include "m2c_macros.h"

void *memcpy(void *dst, void *src, u32 n);
void func_00129C28(void *dst, void *src);
f32 func_00129CD8(void *a, void *b);
void func_00129BB8(void *a0, void *a1, f32 f12);
s32 rand(void);
f32 sqrtf(f32 x);
extern f32 D_00385184;
extern f32 D_00385188;
extern f32 D_0038518C;

void func_001C78A0(u8 *s1, u8 *s3) {
    u8 *s4;
    u8 *s5;
    u8 *p;
    s32 i;
    s32 rnd;
    f32 len;
    f32 f1;
    f32 f0;

    s4 = s3 + 0x30;
    s5 = s3 + 0x20;
    p = s1;
    for (i = 0; i < 10; i++) {
        func_00129C28(p, s5);
        func_00129C28(p + 0x10, s4);
        p += 0x50;
    }
    len = func_00129CD8(s4, s4);
    f1 = sqrtf(len);
    if (f1 != f1) {
        f1 = sqrtf(len);
    }
    f0 = *(f32 *)(s3 + 0x40);
    *(f32 *)(s1 + 0x3B4) = f1 / f0;
    memcpy(s1 + 0x330, s3, 0x60);
    func_00129BB8(s1 + 0x3A0, s4, *(f32 *)(s3 + 0x40));
    *(f32 *)(s1 + 0x3C0) = 128.0f;
    *(f32 *)(s1 + 0x3B0) = D_00385184;
    *(u16 *)(s1 + 0x3C4) = 2;
    *(s32 *)(s1 + 0x390) = 2;
    *(s32 *)(s1 + 0x394) = 2;
    *(s32 *)(s1 + 0x398) = *(s32 *)(s3 + 0x4C);
    rnd = rand();
    f0 = (f32)rnd;
    f0 = f0 / D_00385188;
    *(f32 *)(s1 + 0x328) = D_0038518C;
    *(f32 *)(s1 + 0x320) = 1.0f;
    *(f32 *)(s1 + 0x324) = 1.5f;
    *(f32 *)(s1 + 0x3B8) = f0 * 20.0f + 10.0f;
    *(f32 *)(s1 + 0x3BC) = f0 * 20.0f + 10.0f;
}
