#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, s32 *arg2, s32 arg3);
extern u8 D_00340248[];
extern u8 *D_00387760;

void func_00148888(s32 arg0) {
    s32 sp[2];
    u8 *temp_s0;

    if (D_00387760 == NULL) {
        return;
    }
    temp_s0 = *(u8 **)(D_00387760 + 4) + (arg0 * 0x270);
    if (*(s32 *)(temp_s0 + 0x25C) == 0) {
        sp[0] = arg0;
        sp[1] = 0;
        *(s32 *)(temp_s0 + 0x25C) = BtlTaskList_AddTail(*(s32 *)D_00387760, D_00340248, sp, arg0);
    }
}
