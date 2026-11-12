#include "m2c_macros.h"

s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001F9DB8(void *arg0, s32 arg1) {
    func_002113C0((s32)arg0, 2, 0x20, 1);
    *(s32 *)((u8 *)arg0 + 0x8E4) = arg1;
}
