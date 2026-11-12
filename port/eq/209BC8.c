#include "common.h"

extern u8 *D_00387930;
s32 func_00211288(s32 arg0, s32 arg1);
s32 func_003126C8(s32 arg0, s32 arg1);

s32 func_00209BC8(u32 arg0, s32 arg1) {
    s32 r = (arg0 < 2);

    if (D_00387930 == 0) {
        return r;
    }
    if (r == 0) {
        return 0;
    }
    {
        s32 x = func_00211288((s32)arg0, arg1);

        return func_003126C8(arg1, x + 0x1C0);
    }
}
