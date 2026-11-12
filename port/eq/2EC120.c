#include "common.h"

s32 func_002EA050(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
s32 func_002EBF28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern u8 D_0037BF00[] __attribute__((section(".data")));

s32 func_002EC120(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    if (arg2 & 0x3F) {
        func_002EA050((s32)D_0037BF00, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return -3;
    }
    return func_002EBF28(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
