#include "m2c_macros.h"

s32 func_003FB7B0(s32 arg0) {
    s32 h;
    s32 m;
    s32 s;
    s32 temp_v0;

    h = arg0 / 3600;
    m = (arg0 - h * 3600) / 60;
    s = (arg0 - h * 3600) - m * 60;
    temp_v0 = h * 0x2710 + m * 0x64 + s;
    return (temp_v0 > 0x176D7) ? 0x176D7 : temp_v0;
}
