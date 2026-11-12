#include "common.h"

void func_002CE740(s32 arg0);
s32 func_002CE760(s32 arg0);
s32 func_002CE7C0(s32 arg0);

s32 func_002CE6D8(s32 arg0) {
    s32 temp_s0;
    s32 var_v0;

    var_v0 = 0;
    if (*(s32 *)((u8 *)arg0 + 0x48) != 1) {
        var_v0 = func_002CE760(1);
        if (var_v0 == 0) {
            *(s32 *)((u8 *)arg0 + 0x4C) = 0;
            *(s32 *)((u8 *)arg0 + 0x48) = 0;
            func_002CE740(1);
            temp_s0 = func_002CE7C0(arg0);
            func_002CE740(0);
            var_v0 = temp_s0;
        }
    }
    return var_v0;
}
