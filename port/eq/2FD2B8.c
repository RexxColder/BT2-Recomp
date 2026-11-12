#include "common.h"

s32 func_002FEBB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern u8 D_00356018[] __attribute__((section(".data")));

void *func_002FD2B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_002FEBB8(0, arg1, arg2, arg3, arg4, arg5);
    return D_00356018;
}
