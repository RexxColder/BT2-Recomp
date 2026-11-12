#include "common.h"

void func_002BA180(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_002B5180(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (*(s32 *)((u8 *)arg0 + 0x190) < *(s32 *)((u8 *)arg1 + 0x30)) {
        func_002BA180(arg0, arg1, arg2, arg3, arg4, arg5);
    }
    *(s32 *)((u8 *)arg0 + 0x190) = *(s32 *)((u8 *)arg1 + 0x30);
}
