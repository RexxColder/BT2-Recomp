#include "common.h"

f32 Mathf_Asin(f32 farg0);
void Mtx_RotateX(f32 farg0, void *arg0, void *arg1);
void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
void Vec3_Normalize(void *arg0, s32 arg1, s32 arg2, s32 arg3);
f32 atan2f(f32 farg0, f32 farg1);
extern s32 EftPtcl4_Update __attribute__((section(".data")));

s32 EftPtcl4_SetDir(u8 *arg0, s32 arg1) {
    s32 var_v0;
    s32 a2;
    u8 *s0;
    u8 *s1;
    u8 *s2;

    var_v0 = 0;
    if (arg0 != NULL) {
        a2 = *(s32 *)(*(u8 **)(arg0 + 0x28));
        if (a2 == 0x001C05F8 /* PS2 address of EftPtcl4_Update */) {
            s0 = *(u8 **)(arg0 + 0x38);
            s1 = s0 + 0x10;
            s2 = s0 + 0xC0;
            if (*(s32 *)(s0 + 0x60) & 1) {
                Vec3_Normalize(s0 + 0x30, arg1, a2, (s32)arg0);
                *(f32 *)(s1 + 0x2C) = 1.0f;
                *(f32 *)(s0 + 0x100) = Mathf_Asin(-*(f32 *)(s1 + 0x24));
                *(f32 *)(s0 + 0x104) = atan2f(*(f32 *)(s1 + 0x20), *(f32 *)(s1 + 0x28));
                Mtx_RotateX(*(f32 *)(s0 + 0x100), s2, s0 + 0x80);
                Mtx_RotateY(*(f32 *)(s0 + 0x104), s2, s2);
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
