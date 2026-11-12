#include "common.h"

void func_002C2FF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C3210(s32 arg0, s32 arg1, s32 arg2);

void func_002D22A0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;

    temp_a2 = arg0 + 0xD30;
    if (func_002C3210(arg0, arg1, arg2) != 0) {
        func_002C2FF0(0, 0xFF000125, temp_a2);
        return;
    }
    *(s32 *) (temp_a2 + 0x2B8) = arg2;
    *(s32 *) (temp_a2 + 0x2B4) = arg1;
    *(s32 *) (temp_a2 + 0x2B0) = *(s32 *) (temp_a2 + 0x2B0) + 1;
    *(s32 *) (arg0 + 0x44) = 1;
}
