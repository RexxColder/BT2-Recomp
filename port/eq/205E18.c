#include "common.h"

s32 func_0025FBE8(s32 arg0, s64 arg1);
void func_001B56D8(s32 arg0, s32 arg1);

/* 0x00205E18: if func_0025FBE8(arg0->0x1530, (s64)0x8000 << 27) != 0, tail call func_001B56D8(arg0->0x1534, 0). */
void func_00205E18(u8 *arg0) {
    if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), (s64)0x8000 << 27) != 0) {
        func_001B56D8(*(s32 *)(arg0 + 0x1534), 0);
    }
}
