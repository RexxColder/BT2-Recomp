#include "common.h"

void func_001E0068(u8 *arg0, s32 arg1, s32 arg2);

void func_001E00F0(u8 *arg0, s32 arg1) {
    func_001E0068(arg0, *(s32 *)(arg0 + 0x21C0), arg1 & 0xFF);
}
