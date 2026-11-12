#include "common.h"

void func_001DFEB8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001DFF50(u8 *arg0, s32 arg1, s32 arg2) {
    func_001DFEB8(arg0, arg1, *(s32 *)(arg0 + 0x21C0), arg2 & 0xFF);
}
