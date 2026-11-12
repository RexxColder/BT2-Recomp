#include "common.h"

f32 Mathf_Asin(f32 arg0);
void Mtx_RotateX(void *arg0, void *arg1, f32 farg2);
void Mtx_RotateY(void *arg0, void *arg1, f32 farg2);
void Vec4_Set(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 f0, f32 f1, f32 f2, f32 f3);
f32 atan2f(f32 arg0, f32 arg1);
void func_00129C28(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00194948(void);

s32 func_00194FA8(void *arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_v0;
    u8 *temp_s0;
    u8 *temp_s1;
    u8 *temp_s2;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_a2 = *(s32 *)(*(u8 **)((u8 *)arg0 + 0x28));
        if (temp_a2 == (s32)0x00194948 /* PS2 class address (class 1: the table holds PS2 addresses) */) {
            temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
            temp_s1 = temp_s0 + 0x10;
            temp_s2 = temp_s0 + 0x170;
            if (*(s32 *)(temp_s0 + 0x60) & 1) {
                if (*(u8 *)(*(u8 **)(temp_s1 + 0x38) + 1) == 1) {
                    Vec4_Set(temp_s0 + 0x30, arg1, temp_a2, (s32)arg0, 0.0f, 0.0f, 1.0f, 1.0f);
                } else {
                    func_00129C28(temp_s0 + 0x30, arg1, temp_a2, (s32)arg0);
                }
                *(f32 *)(temp_s0 + 0x1B0) = Mathf_Asin(-*(f32 *)(temp_s1 + 0x24));
                *(f32 *)(temp_s0 + 0x1B4) = atan2f(*(f32 *)(temp_s1 + 0x20), *(f32 *)(temp_s1 + 0x28));
                Mtx_RotateX(temp_s2, temp_s0 + 0x130, *(f32 *)(temp_s0 + 0x1B0));
                Mtx_RotateY(temp_s2, temp_s2, *(f32 *)(temp_s0 + 0x1B4));
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
