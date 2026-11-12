#include "common.h"

void func_002BAAD0(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_002BAAA8(s32 arg0, u8 *arg1, s32 arg2, s32 arg3) {
    func_002BAAD0(arg0, arg1, arg2, arg3, 0, 0, *(s32 *)(arg1 + 0xC), *(s32 *)(arg1 + 0x10));
}
