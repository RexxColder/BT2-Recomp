#include "common.h"

f32 Mathf_Asin(f32 arg0);
void Mtx_RotateX(void *arg0, void *arg1, f32 farg2);
void Mtx_RotateY(void *arg0, void *arg1, f32 farg2);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
f32 atan2f(f32 arg0, f32 arg1);
void func_00129C38(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 EftPtcl3_Update[];

s32 EftPtcl3_SetTarget(void *arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_a2;
    s32 var_v0;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *temp_s3;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_a2 = *(s32 *)(*(u8 **)((u8 *)arg0 + 0x28));
        if (temp_a2 == 0x001BC188 /* PS2 address of EftPtcl3_Update */) {
            temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
            temp_s2 = temp_s0 + 0x150;
            temp_s1 = temp_s0 + 0x160;
            temp_s3 = temp_s0 + 0x170;
            if (*(s32 *)(temp_s0 + 0x60) & 1) {
                func_00129C38(temp_s2, arg1, temp_a2, (s32)arg0);
                Vec3_Sub(temp_s1, temp_s2, temp_s0 + 0x20);
                Vec3_Normalize(temp_s1, temp_s1);
                temp_f20 = Mathf_Asin(-*(f32 *)(temp_s0 + 0x164));
                temp_f21 = atan2f(*(f32 *)(temp_s1 + 0), *(f32 *)(temp_s0 + 0x168));
                Mtx_RotateX(temp_s3, temp_s0 + 0x1D0, temp_f20);
                Mtx_RotateY(temp_s3, temp_s3, temp_f21);
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
