#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2, s64 arg3);
extern u8 D_00342950[] __attribute__((section(".data")));
extern s32 D_00387894;

s32 func_001C1198(s32 arg0) {
    s64 buf[14];
    s64 a3;
    s32 i;

    for (i = 0; i < 14; i++) {
        buf[i] = *(s64 *)(arg0 + i * 8);
    }
    a3 = *(s64 *)(arg0 + 0x50);
    return BtlTaskList_AddTail(*(s32 *)D_00387894, (s32)D_00342950, (s32)buf, a3);
}
