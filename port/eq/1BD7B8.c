#include "common.h"

f32 Mathf_Asin(f32 farg0);
void Mtx_RotateX(f32 farg0, s32 arg0, s32 arg1);
void Mtx_RotateY(f32 farg0, s32 arg0, s32 arg1);
void Mtx_StoreIdentity(s32 arg0);
f32 atan2f(f32 farg0, f32 farg1);
s32 rand(void);
extern f32 D_00385124;
extern f32 D_00385128;
extern f32 D_0038512C;
extern f32 D_00385130;
extern f32 D_00385134;

void func_001BD7B8(u8 *arg0, u8 *arg1) {
    u8 *s2;
    u8 *s3;
    u8 *s4;
    s32 v0;
    f32 f1;
    f32 f4;
    f32 var_f0;

    s2 = arg0 + 0x80;
    s3 = arg0 + 0xC0;
    v0 = *(s32 *)(arg0 + 0x60);
    s4 = *(u8 **)(arg1 + 0x38);
    *(s32 *)(arg0 + 0x60) = v0 | 1;
    f1 = *(f32 *)(arg1 + 0);
    if (f1 <= 0.0f) {
        *(s32 *)(arg0 + 0x60) = v0 | 9;
    } else {
        *(f32 *)(arg0 + 0x70) = f1 * 30.0f;
    }

    Mtx_StoreIdentity((s32)s2);
    *(f32 *)(arg0 + 0x100) = Mathf_Asin(-*(f32 *)(arg1 + 0x24));
    *(f32 *)(arg0 + 0x104) = atan2f(*(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x28));
    Mtx_RotateX(*(f32 *)(arg0 + 0x100), (s32)s3, (s32)s2);
    Mtx_RotateY(*(f32 *)(arg0 + 0x104), (s32)s3, (s32)s3);
    f4 = *(f32 *)(s4 + 0x10) + (*(f32 *)(s4 + 0x14) * ((f32)rand() / D_00385124));
    *(f32 *)(arg0 + 0x108) = f4;
    if (D_00385128 <= f4) {
        var_f0 = f4 - D_0038512C;
        *(f32 *)(arg0 + 0x108) = var_f0;
    } else if (f4 <= D_00385130) {
        var_f0 = f4 + D_00385134;
        *(f32 *)(arg0 + 0x108) = var_f0;
    }
}
