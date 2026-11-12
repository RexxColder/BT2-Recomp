#include "common.h"

void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);

void func_002CD380(u8 *arg0) {
    u8 *s0;

    s0 = arg0 + 0xA0C;
    if (*(s32 *)(s0 + 0x18) == 0 && *(s32 *)(s0 + 0x3C) == 2) {
        func_002D05E8((s32)arg0, 0xF, 1);
    }
    if (*(s32 *)(s0 + 0x14) != 0) {
        return;
    }
    if (*(s32 *)(s0 + 0x3C) == 1) {
        func_002D05E8((s32)arg0, 0xF, 2);
    }
}
