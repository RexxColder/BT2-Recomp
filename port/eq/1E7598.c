#include "m2c_macros.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00343538 __attribute__((section(".data")));
extern u8 *D_003878F4;

void func_001E7598(s32 arg0) {
    s32 sp[4];
    u8 *g = D_003878F4;

    if (*(s32 *)(g + 4) == 0) {
        sp[0] = arg0;
        *(s32 *)(g + 4) = BtlTaskList_AddTail(*(s32 *)g, (s32)&D_00343538, (s32)sp);
    }
}
