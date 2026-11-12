#include "common.h"

void func_002B74F8(s32 arg0, s32 arg1);

void func_002B7590(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002B74F8(arg0, arg1);
    *(s32 *)((u8 *)arg0 + 0x1B4) = arg2;
    *(s32 *)((u8 *)arg0 + 0x1B8) = arg3;
    *(s32 *)((u8 *)arg0 + 0x1AC) = 1;
    *(s32 *)((u8 *)arg0 + 0x1B0) = 0;
}
