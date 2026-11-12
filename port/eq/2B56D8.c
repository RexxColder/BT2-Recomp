#include "common.h"

s32 func_002B57A0(s32 arg0);
s32 func_002B57E0(s32 arg0);

void func_002B56D8(u8 *arg0, u8 *arg1) {
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_v0;

    temp_s7 = *(s32 *)(arg0 + 0);
    temp_s6 = *(s32 *)(arg0 + 0xC);
    temp_s5 = func_002B57A0(*(s32 *)(arg0 + 8));
    temp_s2 = *(s32 *)(arg0 + 0x10);
    temp_s3 = *(s32 *)(arg0 + 0x14);
    temp_s4 = *(s32 *)(arg0 + 0x18);
    temp_v0 = func_002B57E0(*(s32 *)(arg0 + 0x1C));
    *(s32 *)(arg1 + 0x20) = temp_s7;
    *(s32 *)(arg1 + 0x1C) = temp_s5;
    *(s32 *)(arg1 + 0) = temp_s6;
    *(s32 *)(arg1 + 4) = temp_s2;
    *(s32 *)(arg1 + 8) = temp_s3;
    *(s32 *)(arg1 + 0xC) = temp_s4;
    *(s32 *)(arg1 + 0x2C) = *(s32 *)(arg0 + 0x30);
    *(s32 *)(arg1 + 0x10) = temp_v0;
    *(s32 *)(arg1 + 0x14) = *(s32 *)(arg0 + 0x28);
    *(s32 *)(arg1 + 0x18) = *(s32 *)(arg0 + 0x2C);
    *(s32 *)(arg1 + 0x24) = *(s32 *)(arg0 + 0x3C);
    *(s32 *)(arg1 + 0x28) = *(s32 *)(arg0 + 0x40);
}
