#include "common.h"

void func_002EFE38(s32 arg0, s32, s32);
s32 func_002F14C8(s32 arg0);
s32 func_002F14F8(s32 arg0);
s32 func_002F1540(s32 arg0);

void func_002F46B0(u8 *arg0, s32 *arg1, s32 *arg2) {
    u8 temp_v0;
    s32 q;

    temp_v0 = *(u8 *)(arg0 + 1);
    if ((u32)(temp_v0 - 3) < 2U) {
        func_002EFE38(*(s32 *)(arg0 + 0xC), arg1, arg2);
    } else if ((s8)temp_v0 != 5) {
        *arg1 = 0;
        *arg2 = 1;
    } else {
        *arg1 = func_002F1540(*(s32 *)(arg0 + 4));
        *arg2 = func_002F14C8(*(s32 *)(arg0 + 4));
        q = func_002F14F8(*(s32 *)(arg0 + 4));
        *arg1 = *arg1 * (0x10 / q);
    }
    *arg1 += *(s32 *)(arg0 + 0x88);
}
