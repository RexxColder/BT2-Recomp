#include "common.h"

f32 Mathf_Asin(f32 farg0);
void Mtx_RotateX(f32 farg0, u8 *arg1, u8 *arg2);
void Mtx_RotateY(f32 farg0, u8 *arg1, u8 *arg2);
void Mtx_StoreIdentity(u8 *arg0);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
f32 atan2f(f32 farg0, f32 farg1);

void func_001C9D50(u8 *arg0, u8 *arg1) {
    f32 temp_f1;
    f32 var_f20;
    f32 var_f21;
    s32 temp_v1;
    u8 *var_s2;
    u8 *var_s3;
    u8 *var_s4;

    var_s2 = arg1 + 0x20;
    var_s3 = arg0 + 0xC0;
    var_s4 = arg0 + 0x80;
    var_f21 = 0.0f;
    temp_v1 = *(s32 *)(arg0 + 0x50);
    *(s32 *)(arg0 + 0x50) = temp_v1 | 1;
    temp_f1 = *(f32 *)(arg1 + 8);
    if (temp_f1 <= 0.0f) {
        *(s32 *)(arg0 + 0x50) = temp_v1 | 9;
    } else {
        *(f32 *)(arg0 + 0x6C) = temp_f1 * 30.0f;
    }
    Vec3_Normalize(var_s2, var_s2);
    Mtx_StoreIdentity(var_s4);
    var_f20 = Mathf_Asin(-*(f32 *)(arg1 + 0x24));
    var_f21 = atan2f(*(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x28));
    Mtx_RotateX(var_f20, var_s3, var_s4);
    Mtx_RotateY(var_f21, var_s3, var_s3);
    *(s32 *)(arg0 + 0x70) = 0;
    *(s32 *)(arg0 + 0x74) = 0;
}
