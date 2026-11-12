#include "common.h"

s32 func_002B24C8(s32 arg0, s32 arg1, s32 arg2);

s32 func_0025EF60(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 ret;
    s32 p;

    if (arg2 >= 0x1B1) {
        ret = *(s32 *)((u8 *)arg0 + arg2 * 4 + 0x60);
        *arg3 = 1;
        return ret;
    }
    p = *(s32 *)((u8 *)arg0 + arg2 * 4 + 0x60);
    if (p != 0) {
        func_002B24C8(p, arg1, (s32)arg3);
        ret = arg1;
    } else {
        ret = 0;
    }
    return ret;
}
