#include "common.h"

s32 func_002CCC00(s32 arg0, s32 arg1);
void func_002D1FD0(s32 arg0, s32 arg1);

s32 func_002CCB98(s32 arg0, s32 arg1) {
    if ((u32)(*(s32 *)((u8 *)arg0 + 0x4C) - 3) < 2U) {
        func_002D1FD0(arg0, arg1);
        return func_002CCC00(arg0, arg1);
    }
    return 0;
}
