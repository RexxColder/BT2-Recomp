#include "common.h"

void func_002115B0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *p = (s32 *)(arg0 + arg1 * 4 + 0x2B0);

    *p = *p ^ arg2;
}
