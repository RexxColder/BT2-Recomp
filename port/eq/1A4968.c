#include "common.h"

f32 Mathf_Asin(f32 farg0);
void Mtx_RotateX(f32 farg0, void *arg1, void *arg2);
void Mtx_RotateY(f32 farg0, void *arg1, void *arg2);
void Mtx_StoreIdentity(void *arg0);
void Vec3_Normalize(void *arg0, void *arg1);
f32 atan2f(f32 farg0, f32 farg1);

s32 func_001A4968(u8 *arg0, void *arg1) {
    f32 var_f20;
    f32 var_f21;
    s32 var_v0;
    u8 *var_s0;
    u8 *var_s1;

    var_v0 = 0;
    if (arg0 != NULL) {
        var_s1 = *(u8 **)(arg0 + 0x38);
        if (var_s1 != NULL && (*(s32 *)(var_s1 + 0x50) & 1)) {
            var_s0 = var_s1 + 0x10;
            Vec3_Normalize(var_s1 + 0x30, arg1);
            var_s1 += 0xC0;
            var_f21 = Mathf_Asin(*(f32 *)(var_s0 + 0x24));
            var_f20 = atan2f(-*(f32 *)(var_s0 + 0x20), -*(f32 *)(var_s0 + 0x28));
            Mtx_StoreIdentity(var_s1);
            Mtx_RotateX(var_f21, var_s1, var_s1);
            Mtx_RotateY(var_f20, var_s1, var_s1);
            var_v0 = 1;
        }
    }
    return var_v0;
}
