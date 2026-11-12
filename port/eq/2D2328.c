#include "common.h"

s32 func_002C3210(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3);
s32 func_002C2FF0(s32 arg0, s32 arg1, void *arg2);
void func_002D23F0(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4);

s32 func_002D2328(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 temp_v0;
    u8 *temp_a2;

    *arg3 = 0;
    temp_v0 = func_002C3210(arg0, arg1, arg2, arg3);
    temp_a2 = arg0 + 0xA0C;
    if (temp_v0 != 0) {
        return func_002C2FF0(0, 0xFF000126, temp_a2);
    }
    if (*(s32 *)(temp_a2 + 0x38) != 0) {
        if (*(s32 *)(arg0 + 0x4C) == 4) {
            func_002D23F0(arg0, arg1, arg2, arg3, *(s32 *)(temp_a2 + 0xB4));
            return 0;
        }
        *arg3 = 0;
        return temp_v0;
    }
    *arg3 = 1;
    return temp_v0;
}
