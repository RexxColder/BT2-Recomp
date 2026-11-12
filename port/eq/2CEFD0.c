#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002C3210(u8 *arg0);
s32 func_002CF170(u8 *arg0, s32 arg1);
s64 func_002D2750(void);
s32 func_002D2FC8(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 t0);
extern void (*D_00346E6C)(u8 *, s32) __attribute__((section(".data")));

s32 func_002CEFD0(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 temp_s2;
    s32 temp_v1;
    s32 var_v0;

    *arg1 = 0;
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000136, arg2, arg3);
    }
    var_v0 = func_002CF170(arg0, 1);
    if (var_v0 == 0) {
        temp_s2 = func_002D2FC8(arg0, 6, 0xB, arg1, 0);
        if (*arg1 != 0) {
            temp_v1 = *(s32 *)(arg0 + 0x968);
            if (temp_v1 == *(s32 *)(arg0 + 0x96C)) {
                if (temp_v1 == 0) {
                    *(s64 *)(arg0 + 0x3780) = func_002D2750();
                }
                *(s32 *)(arg0 + 0x968) = *(s32 *)(arg0 + 0x968) + 1;
            }
        }
        if (D_00346E6C != NULL) {
            D_00346E6C(arg0, *arg1);
        }
        var_v0 = temp_s2;
    }
    return var_v0;
}
