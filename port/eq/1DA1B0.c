#include "common.h"

s32 func_00129F60(s32 a0, s32 a1, s32 a2, s32 a3, s64 a4, s64 a5, s64 a6, s64 a7,
                  s64 a8, s64 a9, s64 a10, s64 a11, s64 a12, s64 a13, s64 a14, s64 a15);

void func_001DA1B0(s32 arg0, s64 *arg1, s64 *arg2) {
    s64 copy[10];
    int i;

    for (i = 0; i < 8; i++) {
        copy[i] = arg1[i];
    }
    copy[8] = arg2[0];
    copy[9] = arg2[1];
    func_00129F60(arg0, (s32)copy, (s32)&copy[8], 0,
                  arg1[0], arg1[1], arg1[2], arg1[3],
                  arg1[0], arg1[1], arg1[2], arg1[3], arg1[4], arg1[5], arg1[6], arg1[7]);
}
