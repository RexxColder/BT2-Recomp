#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, u8 *arg1, u8 *arg2);
extern s32 D_003878EC;
extern u8 D_003434F0[];

s32 func_001E66A0(u8 *arg0) {
    u8 buf[0x40];

    __builtin_memcpy(buf, arg0, 0x40);
    return BtlTaskList_AddTail(D_003878EC, D_003434F0, buf);
}
