#include "common.h"

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
extern u8 *D_003876A0;
extern u8 *D_003876B0;

s32 func_00104ED0(void *arg0) {
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = *(s32 *)arg0;
    if (temp_v1 != 1) {
        if (temp_v1 < 2) {
            if (temp_v1 != 0) {
                return 1;
            }
            *(s32 *)(D_003876B0 + 8) = func_00100ED0(*(s32 *)((u8 *)arg0 + 0xC), *(s32 *)(D_003876B0 + 8), 1);
            func_00100FC8(1);
            *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | (s64)0x1000;
            *(s32 *)arg0 = *(s32 *)arg0 + 1;
            return 0;
        }
        if (temp_v1 != 2) {
            return 1;
        }
        goto block_10;
    }
    var_v0 = func_00100FC8(0);
    if (var_v0 != 0) {
        *(s32 *)arg0 = *(s32 *)arg0 + 1;
block_10:
        var_v0 = 1;
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & (s64)-0x1001;
        *(s32 *)D_003876B0 = *(s32 *)D_003876B0 + 1;
    }
    return var_v0;
}
