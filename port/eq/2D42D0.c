#include "common.h"

s32 func_002C0D40(u8 *a0, s32 a1, u8 *a2, s32 a3);

s32 func_002D42D0(u8 *arg0, u8 *arg1, s32 arg2) {
    if ((u32)(*(s32 *)(arg0 + 0x48) - 3) >= 2U) {
        *(s32 *)arg1 = 0;
        return 0;
    }
    return func_002C0D40(arg0, *(s32 *)(arg0 + 0x20D8), arg1, arg2);
}
