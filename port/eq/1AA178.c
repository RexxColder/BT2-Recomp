#include "common.h"

extern u8 *D_00387840;
extern s32 D_00387844;
extern u8 D_003426F8[] __attribute__((section(".data")));
s32 BtlTaskList_AddTail(s32 arg0, u8 *arg1, s32 *arg2);

s32 func_001AA178(s32 *arg0) {
    s32 sp[4];
    s32 idx = *arg0;

    sp[0] = idx;
    if (*(u8 *)(D_00387840 + idx + 4) == 0) {
        return BtlTaskList_AddTail(D_00387844, D_003426F8, sp) != 0;
    }
    return 0;
}
