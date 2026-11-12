#include "common.h"

s32 func_002D3030(s32 arg0, s32 arg1);
s32 func_002C0E40(s32 arg0, s32 arg1);
void func_002D3018(s32 arg0, s32 arg1, s32 arg2);

void func_002BF5C0(u8 *arg0) {
    if ((func_002D3030((s32)arg0, 7) != 1) && (func_002C0E40((s32)arg0, *(s32 *)(arg0 + 0x211C)) == 1)) {
        func_002D3018((s32)arg0, 7, 1);
    }
}
