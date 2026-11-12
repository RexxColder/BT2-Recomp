#include "common.h"

s32 func_00126040(s32 arg0);
s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);
s32 func_0020C730(s32 arg0);
s32 func_0020C780(s32 arg0);
s32 func_0020C7D0(s32 arg0);
s32 func_0020C820(s32 arg0);
s32 func_00210DD8(s32 arg0);
u8 *func_00211288(s32 arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);

void func_00124E18(s32 arg0) {
    u8 *temp_s1;
    u8 *temp_v0;
    s32 temp_s0;

    temp_s1 = (u8 *)arg0 + 0x10A0;
    temp_v0 = func_00211288(func_00210DD8(func_00126040(arg0)));
    *(s32 *)(temp_s1 + 0x6C) = 0;
    if (func_00211310(temp_v0, 0, 0x800) != 0) {
        *(s32 *)(temp_s1 + 0x6C) = *(s32 *)(temp_s1 + 0x6C) | 1;
    }
    if (func_00211310(temp_v0, 0, 2) != 0) {
        *(s32 *)(temp_s1 + 0x6C) = *(s32 *)(temp_s1 + 0x6C) | 4;
    }
    if (func_00211310(temp_v0, 0, 4) != 0) {
        *(s32 *)(temp_s1 + 0x6C) = *(s32 *)(temp_s1 + 0x6C) | 8;
    }
    if (func_00211310(temp_v0, 0, 0x4000) != 0) {
        *(s32 *)(temp_s1 + 0x6C) = *(s32 *)(temp_s1 + 0x6C) | 0x10;
    }
    if (func_00211310(temp_v0, 0, 0x400) != 0) {
        *(s32 *)(temp_s1 + 0x6C) = *(s32 *)(temp_s1 + 0x6C) | 0x20;
    }
    temp_s0 = func_0020C730(*(s32 *)(temp_v0 + 0x1534));
    temp_s0 = temp_s0 + func_0020C780(*(s32 *)(temp_v0 + 0x1534));
    temp_s0 = temp_s0 + func_0020C7D0(*(s32 *)(temp_v0 + 0x1534));
    temp_s0 = temp_s0 + func_0020C820(*(s32 *)(temp_v0 + 0x1534));
    if (temp_s0 > 0) {
        *(s32 *)(temp_s1 + 0x6C) = *(s32 *)(temp_s1 + 0x6C) | 2;
    }
    if (func_00126058(arg0, 4, 0x80) != 0) {
        *(s32 *)(temp_s1 + 0x6C) = *(s32 *)(temp_s1 + 0x6C) | 0x40;
    }
    if (!(*(s32 *)(temp_s1 + 0x6C) & 0x20)) {
        *(s32 *)(temp_s1 + 0xFC) = 0;
        return;
    }
    *(s32 *)(temp_s1 + 0xFC) = *(s32 *)(temp_s1 + 0xFC) + 1;
}
