#include "common.h"

s32 func_002EFE50(s32 arg0);
s32 func_002F1330(s32 arg0);
s32 func_002F14C8(s32 arg0);
s32 func_002F14F8(s32 arg0);
s32 func_002F1540(s32 arg0);
s32 func_002F59D8(u8 *arg0, s32 arg1);

void func_002F47C8(u8 *arg0, s32 *arg1, s32 *arg2) {
    u8 temp_v0;
    s32 s0;
    s32 s1;
    s32 v;
    s32 div;

    temp_v0 = *(u8 *)(arg0 + 1);
    if ((u32)((s32)temp_v0 - 3) < 2U) {
        *arg2 = func_002F14C8(*(s32 *)(arg0 + 0x4));
        s1 = func_002F1330(*(s32 *)(arg0 + 0x4));
        s0 = func_002EFE50(*(s32 *)(arg0 + 0xC));
        v = func_002F59D8(arg0, 0);
        *arg1 = (s1 - ((s0 - *(s32 *)(arg0 + 0xA8)) + v)) + *(s32 *)(arg0 + 0xA4);
    } else if (temp_v0 != 5) {
        *arg1 = 0;
        *arg2 = 1;
    } else {
        *arg1 = func_002F1540(*(s32 *)(arg0 + 0x4));
        *arg2 = func_002F14C8(*(s32 *)(arg0 + 0x4));
        div = func_002F14F8(*(s32 *)(arg0 + 0x4));
        *arg1 = *arg1 * (0x10 / div);
        *arg1 = *arg1 + *(s32 *)(arg0 + 0xA4);
    }

    v = *arg1 + *(s32 *)(arg0 + 0x88);
    *arg1 = (v < 0) ? 0 : v;
}
