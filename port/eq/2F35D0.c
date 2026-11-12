#include "common.h"

void func_002FEB98(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002FEBB8(s32 arg0);

void func_002F35D0(s32 arg0) {
    if (arg0 != 0) {
        func_002FEB98(*(s32 *)((u8 *)arg0 + 8), *(s32 *)((u8 *)arg0 + 0xC), *(s32 *)((u8 *)arg0 + 0x10), *(s32 *)((u8 *)arg0 + 4));
        func_002FEBB8(*(s32 *)((u8 *)arg0 + 0));
        return;
    }
    func_002FEB98(0, 0, 0, 0);
    func_002FEBB8(0);
}
