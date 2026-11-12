#include "common.h"

void func_002C1A78(s32 arg0, s32 arg1, void *arg2);
s32 func_002C2428(s32 arg0, s32 arg1);
extern u8 D_0037A2A0[];
extern u8 D_00394678[];

void func_002C1988(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_s2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;

    var_s0 = arg1;
    var_s1 = arg0;
    var_s3 = 0;
    temp_s2 = *(s32 *)((u8 *)arg2 + 0x10);
loop_5:
    if (func_002C2428(var_s1, var_s0) != 0) {
        *(s32 *)(D_00394678 + 0) = 0;
        func_002C1A78(var_s1, var_s0, D_00394678);
        if (*(s32 *)(D_00394678 + 0) != 0) {
            if (*(s32 *)(D_00394678 + 0xC) > 0) {
                *(s32 *)((u8 *)arg2 + 0x1C) = *(s32 *)(D_00394678 + 0xC);
            }
            if (*(s32 *)(D_00394678 + 0x64) > 0) {
                *(s32 *)((u8 *)arg2 + 0x14) = *(s32 *)(D_00394678 + 0x64);
            }
            if (*(s32 *)(D_00394678 + 0x68) > 0) {
                *(s32 *)((u8 *)arg2 + 0x18) = *(s32 *)(D_00394678 + 0x68);
            }
            if (*(s32 *)(D_00394678 + 0x6C) > 0) {
                *(s32 *)((u8 *)arg2 + 0x20) = *(s32 *)(D_00394678 + 0x6C);
                *(u8 **)((u8 *)arg2 + 8) = D_0037A2A0;
            }
        }
    } else {
        var_s0 -= temp_s2;
        var_s1 += temp_s2;
        if ((var_s3 < 3) && (var_s0 > 0)) {
            var_s3 += 1;
            goto loop_5;
        }
    }
}
