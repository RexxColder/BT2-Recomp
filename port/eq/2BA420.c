#include "common.h"

s32 func_002B9FB0(s32 arg0);
s32 func_002D3C88(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002BA420(s32 arg0) {
    s32 ret;

    if (func_002B9FB0(arg0) != 1) {
        ret = 0;
        if (*(s32 *)((u8 *)arg0 + 0x17C) != 0) {
            ret = (func_002D3C88(*(s32 *)((u8 *)arg0 + 0x3C), 2, 0, 0) == 0) ? 0 : -1;
        }
        return ret;
    }
    return 0;
}
