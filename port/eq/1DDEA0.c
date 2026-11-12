#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 rand(void);
s32 BtlTaskList_AddTail(s32 arg0, void *arg1, s32 *arg2, s32 arg3);
extern u8 D_00343228[];
extern s32 *D_003878DC;

void EftBlade_Create(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[0x4A8];

    memset(sp, 0, 0x12A0);
    sp[0x4A0] = arg0;
    sp[0x4A1] = (rand() % 30) + 0x3C;
    BtlTaskList_AddTail(*D_003878DC, D_00343228, sp, arg3);
}
