#include "common.h"

s32 func_0027A448(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
s32 sceGsSyncPath(s32 arg0, s32 arg1);
extern s32 D_003B0A84 __attribute__((section(".data")));

s32 func_0027A970(s32 arg0) {
    s32 s0 = (D_003B0A84 & 1) ? 0xE00 : 0;

    sceGsSyncPath(0, 0);
    func_0027A448(arg0, s0, 0x200, 0xE0, 0);
    return func_0027A448(arg0, s0 + 0x700, 0x200, 0xE0, 1);
}
