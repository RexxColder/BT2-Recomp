#include "common.h"

s32 func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002C0D40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp;

    temp = (u8 *)arg0 + 0x1310 + arg1 * 0x74;
    if (*(s32 *)(temp + 4) == 0) {
        return func_002D2FC8(arg0, *(s32 *)(temp + 0x4C), 0xB, arg2, arg3);
    }
    return 0;
}
