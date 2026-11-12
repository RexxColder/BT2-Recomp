#include "common.h"

void func_002B9430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_002D67C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_002D6180(s32 arg0, s32 arg1);
void func_002D61C8(s32 arg0, s32 arg1, s32 arg2);

void func_002BAAD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 sp[68];
    s32 temp_s0;
    s32 *spA0;

    temp_s0 = *(s32 *)((u8 *)arg0 + 0xA8);
    spA0 = &sp[40];
    func_002B9430(arg0, arg1, (s32)sp, arg3, arg4, arg5, arg6, arg7);
    func_002D67C8(temp_s0, (s32)sp, arg2, (s32)spA0, arg4, arg5, arg6, arg7);
    func_002D6180(temp_s0, arg3);
    func_002D61C8(temp_s0, (s32)sp, (s32)spA0);
}
