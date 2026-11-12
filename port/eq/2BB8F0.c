#include "common.h"

void func_002C33D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002BB8F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s0 = arg0 + (arg1 << 5) + 0x284;
    temp_s1 = *(s32 *) (arg0 + 0x3C);
    temp_s2 = *(s32 *) (temp_s0 + 0x14);
    func_002C33D8(temp_s1, *(s32 *) (temp_s0 + 0x18) + 0xC0, 0, 0, 0);
    func_002C33D8(temp_s1, arg2 + 0xC0, temp_s2, 0, 0);
    *(s32 *) (temp_s0 + 0x18) = arg2;
}
