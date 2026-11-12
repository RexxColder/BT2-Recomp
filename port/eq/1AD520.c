#include "common.h"

extern f32 D_00384F18;
extern f32 D_00384F1C;

void Vec3_Normalize(f32 *arg0, f32 *arg1);
void func_00129BD0(f32 *arg1, f32 *arg2, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
s32 rand(void);

void func_001AD520(u8 *arg0, void *arg1) {
    f32 f20 = D_00384F18;
    f32 f23 = D_00384F1C;
    u8 *s2 = *(u8 **)(arg0 + 0x38);
    u8 *s1 = s2 + 0x120;
    f32 *v;
    s32 cnt = 4;
    s32 t;

    do {
        func_00129C28(s1, arg1);
        v = (f32 *)(s1 + 0x10);
        cnt -= 1;
        *(f32 *)(s1 + 0x10) = (2.0f * ((f32)rand() / f20)) - 1.0f;
        *(f32 *)(s1 + 0x14) = -((f32)rand() / f20);
        t = rand();
        *(f32 *)(s1 + 0x1C) = 1.0f;
        *(f32 *)(s1 + 0x18) = (2.0f * ((f32)t / f20)) - 1.0f;
        Vec3_Normalize(v, v);
        func_00129BD0(v, v, 4.0f);
        *(f32 *)(s1 + 0x14) = *(f32 *)(s1 + 0x14) * f23;
        *(f32 *)(s1 + 0x1C) = (((f32)rand() / f20) * 0.5f) + 0.5f;
        s1 += 0x20;
    } while (cnt >= 0);
    *(s32 *)(s2 + 0xC0) = *(s32 *)(s2 + 0xC0) | 0x800;
}
