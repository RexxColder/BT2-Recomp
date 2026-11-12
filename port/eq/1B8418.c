#include "common.h"

void func_0012EAA8(void);
void func_0012EB10(s64 arg0);
void func_0012EB68(void);
void func_0012ECA8(void);
void func_001B85B8(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5);

void func_001B8418(u8 *arg0) {
    u8 *var_s0;
    u8 *temp_s2;
    s32 var_s1;
    s32 t0;
    s32 ti;
    f32 f0;
    f32 fr;

    var_s1 = 9;
    var_s0 = *(u8 **)(arg0 + 0x68);
    temp_s2 = *(u8 **)(arg0 + 0x6C) + (*(s32 *)(arg0 + 0x5C) << 4);
    func_0012EB68();
    func_0012EAA8();
    func_0012EB10(0x48);
    do {
        if (*(s32 *)(var_s0 + 0x5C) & 1) {
            f0 = *(f32 *)(var_s0 + 0x40) * 4096.0f;
            if (f0 >= 2147483648.0f) {
                f0 = f0 - 2147483648.0f;
                ti = (s32)f0;
                fr = f0 - (f32)ti;
                if (fr > 0.5f || (fr == 0.5f && (ti & 1))) {
                    ti++;
                } else if (fr < -0.5f || (fr == -0.5f && (ti & 1))) {
                    ti--;
                }
                t0 = (s32)((u32)ti | 0x80000000u);
            } else {
                ti = (s32)f0;
                fr = f0 - (f32)ti;
                if (fr > 0.5f || (fr == 0.5f && (ti & 1))) {
                    ti++;
                } else if (fr < -0.5f || (fr == -0.5f && (ti & 1))) {
                    ti--;
                }
                t0 = ti;
            }
            func_001B85B8(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, var_s0 + 0x30, var_s0, 0x10, 0x10, t0, temp_s2);
        }
        var_s1 -= 1;
        var_s0 += 0x60;
    } while (var_s1 >= 0);
    func_0012ECA8();
}
