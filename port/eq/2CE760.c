#include "common.h"

s32 func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002CE760(u8 *arg0) {
    s32 ret = 0;

    if (*(s32 *)(arg0 + 0x48) != 4) {
        goto set_flags;
    }
    ret = func_002D2FC8((s32)arg0, 7, 7, 0, 0);
    if (ret != 0) {
        return ret;
    }
set_flags:
    *(s32 *)(arg0 + 0x4C) = 1;
    *(s32 *)(arg0 + 0x48) = 1;
    return 0;
}
