#include "common.h"

s32 func_002C0178(u8 *arg0, s32 arg1, s32 *arg2);

void func_002BE660(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 sp[2];

    func_002C0178(arg0, *(s32 *)(arg0 + 0x200C), sp);
    *arg1 = sp[0];
    *arg2 = sp[1];
}
