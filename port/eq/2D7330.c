#include "common.h"

void func_002D7358(u8 *arg0, s32 arg1, s32 arg2);

void func_002D7330(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x10) = arg2;
    *(s32 *)(arg0 + 0x8) = 1;
    *(s32 *)(arg0 + 0xC) = arg1;
    func_002D7358(arg0, arg1, arg2);
}
