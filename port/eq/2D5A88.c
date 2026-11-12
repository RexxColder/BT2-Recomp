#include "m2c_macros.h"

s32 func_002D5B08(s32 arg0);

s32 func_002D5A88(s32 arg0, void *arg1) {
    s32 var_v0 = 0;
    u8 temp_v1;

    if (func_002D5B08(arg0) == 0xC0) {
        temp_v1 = *(u8 *)((u8 *)arg1 + 0x20);
        var_v0 = (temp_v1 >= 2U) ? 0 : (temp_v1 != 0);
    }
    return var_v0;
}
