#include "common.h"

s32 func_00129C38(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_003877BC;

void func_00190680(u8 *arg0, s64 *arg1, s32 arg2, s32 arg3) {
    s64 sp[2];
    u8 *temp_a0;

    sp[0] = arg1[0];
    sp[1] = arg1[1];
    if (D_003877BC != 0 && arg0 != NULL) {
        temp_a0 = *(u8 **)(arg0 + 0x38);
        if (temp_a0 != NULL && (*(u16 *)(temp_a0 + 0x44) & 2)) {
            func_00129C38((s32)(temp_a0 + 0x10), (s32)sp, D_003877BC, arg3);
        }
    }
}
