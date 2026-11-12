#include "common.h"

void func_001DFCA0(u8 *arg0, s32 arg1, s32 arg2);

void func_001DFD28(u8 *arg0, s32 arg1) {
    func_001DFCA0(arg0, *(s32 *)(arg0 + 0x21C0), arg1 & 0xFF);
}
