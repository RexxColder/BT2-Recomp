#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2, s64 arg3);
extern u8 D_00342848[] __attribute__((section(".data")));
extern s32 D_0038787C;

s32 func_001B5550(s32 arg0) {
    s64 buf[8];
    s32 ret = 0;
    s32 i;

    if (D_0038787C != 0) {
        for (i = 0; i < 8; i++) {
            buf[i] = *(s64 *)(arg0 + i * 8);
        }
        ret = BtlTaskList_AddTail(*(s32 *)D_0038787C, (s32)D_00342848, (s32)buf, *(s64 *)(arg0 + 0x28));
    }
    return ret;
}
