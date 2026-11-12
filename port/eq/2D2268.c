#include "common.h"

void func_002D23F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002D2268(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 var_v0;
    s32 t0;

    var_v0 = 1;
    if (*(s32 *)((u8 *)arg0 + 0xA0C + 0x38) == 0) {
        t0 = *(s32 *)((u8 *)arg0 + 0xA0C + 0xB0);
        func_002D23F0(arg0, arg1, arg2, (s32)sp, t0);
        var_v0 = sp[0];
    }
    return var_v0;
}
