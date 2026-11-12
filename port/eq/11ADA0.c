#include "common.h"

s32 ColBox_Overlaps(u8 *arg0, u8 *arg1);
s32 ColSphere_SweepSphere(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 *arg4);
s32 ColSphere_TestSphere(u8 *arg0, u8 *arg1);
f32 Vec3_Dist(u8 *arg0, u8 *arg1);
void func_003126C8(void *arg0, f32 *arg1);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00384044;

s32 func_0011ADA0(u8 *arg0, u8 *arg1) {
    f32 out;
    f32 var_f20;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    s32 var_s5;
    s32 flag;
    u8 *s1;
    u8 *s3;
    u8 *temp_s2;

    var_s5 = 0;
    var_f20 = 1.0f;
    s1 = *(u8 **)(arg1 + 0x10);
    if (ColBox_Overlaps(arg1 + 0x84, arg0 + 0xF78) == 0) {
        return 0;
    }

    s3 = *(u8 **)(arg0 + 0xEF0);
    for (;;) {
        temp_s2 = s3 + 0x20;
        if (ColSphere_SweepSphere(s1, temp_s2, arg1 + 0xA0, D_002C3630, &out) != 0) {
            if ((out <= D_00384044) || (out >= 1.0f)) {
                if (ColSphere_TestSphere(s1, temp_s2) != 0) {
                    func_003126C8(arg1 + 0x20, (f32 *)s1);
                    var_s5 += 1;
                    func_003126C8(arg1 + 0x30, (f32 *)s1);
                    break;
                }
            } else if (out < var_f20) {
                var_f20 = out;
                var_s5 += 1;
                temp_f3 = *(f32 *)s1 + (out * *(f32 *)(arg1 + 0xA0));
                *(f32 *)(arg1 + 0x20) = temp_f3;
                temp_f1 = *(f32 *)(s1 + 4) + (out * *(f32 *)(arg1 + 0xA4));
                *(f32 *)(arg1 + 0x24) = temp_f1;
                *(f32 *)(arg1 + 0x2C) = 1.0f;
                temp_f2 = *(f32 *)(s1 + 8) + (out * *(f32 *)(arg1 + 0xA8));
                *(f32 *)(arg1 + 0x28) = temp_f2;
                *(f32 *)(arg1 + 0x30) = temp_f3 + (*(f32 *)(s1 + 0x10) * *(f32 *)(arg1 + 0xB0));
                *(f32 *)(arg1 + 0x34) = temp_f1 + (*(f32 *)(s1 + 0x10) * *(f32 *)(arg1 + 0xB4));
                *(f32 *)(arg1 + 0x38) = temp_f2 + (*(f32 *)(s1 + 0x10) * *(f32 *)(arg1 + 0xB8));
            }
        }
        /* flag is read from the element before the stride step */
        flag = *(s32 *)s3;
        s3 += 0x1D0;
        if (flag & 1) {
            break;
        }
    }

    if (var_s5 != 0) {
        *(f32 *)(arg1 + 0xC0) = Vec3_Dist(s1, arg1 + 0x20);
        return 1;
    }
    return 0;
}
