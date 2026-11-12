#include "common.h"

void func_002FD2E8(s32 arg0, s32 arg1);
extern u8 D_0037E428[] __attribute__((section(".data")));

s32 func_002FDCA0(s32 arg0) {
    if (arg0 == 0) {
        func_002FD2E8(arg0, (s32)D_0037E428);
        return 0;
    }
    if (*(s8 *)((u8 *)arg0 + 2) != 1) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x14) << 11;
}
