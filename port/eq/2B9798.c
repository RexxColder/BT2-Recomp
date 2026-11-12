#include "common.h"

void func_002D6E78(s32 arg0, s32 *arg1, s32 *arg2);

void func_002B9798(u8 *arg0, u8 *arg2) {
    s32 sp[2];

    func_002D6E78(*(s32 *)(arg0 + 0xA8), sp, &sp[1]);
    *(s32 *)(arg2 + 0x58) = 0;
    *(s32 *)(arg2 + 0x50) = sp[0];
    *(s32 *)(arg2 + 0x54) = sp[1];
    *(s32 *)(arg2 + 0x5C) = 0;
}
