#include "m2c_macros.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002BF6E0(s32 arg0);

s32 func_002BF6A0(void *arg0) {
    s32 var_v0;
    s32 temp;

    var_v0 = func_002D07B0((s32)arg0, 6);
    temp = (s32)((u8 *)arg0 + 0x365C);
    if (var_v0 != 0) {
        *(s32 *)((u8 *)arg0 + 0x2114) = temp;
        func_002BF6E0(temp);
        var_v0 = 0;
    }
    return var_v0;
}
