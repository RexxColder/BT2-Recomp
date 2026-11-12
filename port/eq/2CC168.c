#include "common.h"

s32 func_002CB588(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002CB678(s32 arg0, s32 arg1);
s32 func_002CC500(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

s32 func_002CC168(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 temp_v0;

    func_002CB588(arg0, (s32)&sp[0], (s32)&sp[1], (s32)&sp[2], (s32)&sp[3]);
    temp_v0 = func_002CC500((sp[0] & 0x0FFFFFFF) | 0x20000000, sp[1], (sp[2] & 0x0FFFFFFF) | 0x20000000, sp[3], arg1, arg2, 0, 0);
    func_002CB678(arg0, temp_v0);
    return temp_v0;
}
