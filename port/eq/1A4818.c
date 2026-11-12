#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, u8 *arg1, u8 *arg2);
extern s32 D_00387820;
extern u8 D_00342418[];

s32 func_001A4818(u8 *arg0) {
    u8 buf[0x40];

    __builtin_memcpy(buf, arg0, 0x40);
    return BtlTaskList_AddTail(D_00387820, D_00342418, buf);
}
