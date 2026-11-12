#include "common.h"

void func_00129C28(void *arg0, s32 arg1);
void BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);
extern u8 D_003426C8[] __attribute__((section(".data")));
extern s32 *gEftStruggle;

f32 func_001A7A50(s32 arg0) {
    u8 sp[0x320];

    memset(sp, 0, 0x320);
    func_00129C28(sp, arg0);
    BtlTaskList_AddTail(*gEftStruggle, D_003426C8, sp);
    return *(f32 *)(sp + 0x10);
}
