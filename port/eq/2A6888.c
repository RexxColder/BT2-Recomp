#include "common.h"

s32 Gsc_GetInt(s32 arg0);
s32 func_00261558(s32 arg0, s32 arg1);
s32 func_002615B0(s32 arg0);
s32 func_002A0010(s32 arg0);

s32 func_002A6888(s32 arg0, u16 *arg1) {
    s32 s0;
    s32 r;

    s0 = 0;
    if (arg0 == 1) {
        return 0;
    }
    if (arg0 == 0) {
        Gsc_GetInt(arg0);
        r = func_002A0010(0x77);
        *(s32 *)arg1 = r;
        s0 = (r == 0);
        func_00261558(r & 0xFFFF, 1);
        return s0;
    }
    if (arg0 == 2) {
        s0 = (func_002615B0(*arg1) == 0);
        return s0;
    }
    return 0;
}
