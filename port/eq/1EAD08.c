#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, u8 *arg1, s64 *arg2, s64 arg3);
extern u8 D_00343568[] __attribute__((section(".data")));
extern u8 *D_003878F8;

s32 func_001EAD08(u8 *arg0) {
    s64 sp[8];
    s32 v0 = 0;
    s32 i;

    for (i = 0; i < 8; i++) {
        sp[i] = *(s64 *)(arg0 + 8 * i);
    }
    if (D_003878F8 != NULL) {
        v0 = BtlTaskList_AddTail(*(s32 *)(D_003878F8 + 0x2BC4), D_00343568, sp, *(s64 *)(arg0 + 0x18));
    }
    return v0;
}
