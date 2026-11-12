#include "common.h"

s32 func_002D45E8(s32 arg0);

s32 func_002D4E68(s32 arg0, s32 *arg1) {
    u8 *p;
    s32 ret;

    *arg1 = 0;
    p = (u8 *)(*(s32 *)((u8 *)arg0 + 4) + 0xB0);
    ret = func_002D45E8(arg0);
    if (ret != 0) {
        ret = 1;
        *arg1 = *(u8 *)(p + 1);
    }
    return ret;
}
