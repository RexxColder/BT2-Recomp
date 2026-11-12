#include "common.h"

void func_002FC638(s32 arg0, s64 arg1, s32 arg2);
void func_002FC670(void);
void func_00331710(s32 arg0, s32 arg1);
s32 sceLseek(s32 arg0, s64 arg1, s32 arg2, s32 arg3);
s32 sceLseek64(s32 arg0, s64 arg1, s32 arg2, s32 arg3);
extern s32 D_003553A8 __attribute__((section(".data")));
extern u8 D_0037E0A0[] __attribute__((section(".data")));
extern u8 D_0037E0C0[] __attribute__((section(".data")));

s32 func_002FC730(s32 arg0, s64 arg1, s32 arg2) {
    s32 var_s0;

    func_002FC638(arg0, arg1, arg2);
    if (D_003553A8 == 1) {
        var_s0 = sceLseek64(arg0, arg1, arg2, D_003553A8);
        if (var_s0 < 0) {
            func_00331710((s32)D_0037E0A0, var_s0);
        }
    } else {
        var_s0 = sceLseek(arg0, (s64)(s32)arg1, arg2, D_003553A8);
        if (var_s0 < 0) {
            func_00331710((s32)D_0037E0C0, var_s0);
        }
    }
    func_002FC670();
    return var_s0;
}
