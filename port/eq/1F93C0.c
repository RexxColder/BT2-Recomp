#include "common.h"

void func_001F93C0(u8 *arg0, s32 arg1, s8 arg2, s32 arg3) {
    u8 *p = arg0 + arg1 * 0x14;

    if (arg3 != 0) {
        *(u8 *)(p + 0xAF0 + 0x12) = (u8)(*(u8 *)(p + 0xAF0 + 0x12) + arg2);
        return;
    }
    *(s8 *)(p + 0xB02) = arg2;
}
