#include "common.h"

s32 func_002E7B90(s32 arg0);
s32 func_002E7F90(s32 arg0);
s32 func_002E7F98(s32 arg0);

void func_002F0E50(u8 *arg0) {
    s32 s1;
    s32 s0;
    s32 s3;
    s32 v0;
    s32 a0;

    s1 = *(s32 *)(arg0 + 4);
    s0 = func_002E7B90(s1);
    s3 = func_002E7F90(s1);
    v0 = func_002E7F98(s1);
    a0 = *(s32 *)(arg0 + 0x34);
    s0 = s0 - a0;
    if (v0 < s0) {
        s0 = v0;
    }
    *(s32 *)(arg0 + 0x34) = a0 + s0;
    *(s32 *)(arg0 + 0x2C) = *(s32 *)(arg0 + 0x2C) + s0;
    *(s32 *)(arg0 + 0x30) = *(s32 *)(arg0 + 0x30) + s3;
}
