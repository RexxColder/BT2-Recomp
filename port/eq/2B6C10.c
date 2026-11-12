#include "common.h"

s32 func_002CEC20(s32 arg0, s32 arg1);

void func_002B6C10(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 buf[8];

    func_002CEC20(*(s32 *)(arg0 + 0x3C), (s32)buf);
    *arg2 = buf[1];
    *arg1 = buf[0];
    *arg3 = buf[5];
}
