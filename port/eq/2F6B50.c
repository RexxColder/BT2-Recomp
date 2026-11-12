#include "m2c_macros.h"

s32 func_002F6B50(u8 *arg0, s32 arg1, s32 *arg2) {
    s32 var_v0 = 0;
    u16 t;
    u16 sw;

    if (arg1 >= 2) {
        t = *(u16 *)arg0;
        sw = (u16)((t >> 8) | (t << 8));
        if (sw == 0x8001) {
            *arg2 = arg1;
            var_v0 = 1;
        }
    }
    return var_v0;
}
