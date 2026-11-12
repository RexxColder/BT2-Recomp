#include "common.h"

void func_002C0E10(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg1 != 8) {
        *(s32 *)(arg0 + arg1 * 116 + 0x1318) = arg2;
    }
}
