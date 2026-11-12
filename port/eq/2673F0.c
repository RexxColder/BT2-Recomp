#include "common.h"

s32 func_00266938(s32 arg0);
void func_00266AF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00266C20(s32 arg0, s32 arg1);
void func_00266DB8(s32 arg0, s32 arg1);
extern u8 *D_003876A0;

void func_002673F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_s1;

    temp_s1 = (s32)(arg0 + 0xDF0);
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) == 0) {
        if (*(s32 *)(arg0 + 0x54) != 0) {
            func_00266AF0((s32)arg0, temp_s1, arg2, arg3, arg4, arg5);
        }
        if ((*(s32 *)(arg0 + 0x754) != 0 && *(s32 *)(arg0 + 0x758) != 0 && *(s32 *)(arg0 + 0x75C) != 0) ||
            func_00266938((s32)arg0) != 0) {
            func_00266C20((s32)arg0, temp_s1);
            func_00266DB8((s32)arg0, temp_s1);
        }
    }
}
