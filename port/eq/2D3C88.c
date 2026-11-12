#include "common.h"

s32 func_002C3210();
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002C00A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D3FD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002D3C88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *s0;
    s32 temp_s2;
    s32 temp_s0_2;

    s0 = (u8 *)(arg0 + 0x2150);
    if (func_002C3210(arg0, arg1, arg2, arg3) != 0) {
        return func_002C2FF0(0, 0xFF000191);
    }
    temp_s2 = *(s32 *)(s0 + 0x10);
    if (temp_s2 == 8) {
        return func_002C2FF0(arg0, 0xFF000602);
    }
    temp_s0_2 = *(s32 *)(s0 + 8) + (arg1 * 0x10) + 4;
    func_002D3FD8(temp_s0_2, arg2, arg3, 0, 0);
    func_002C00A8(arg0, temp_s2, arg1, temp_s0_2);
    return 0;
}
