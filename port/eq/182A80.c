#include "common.h"

void *BtlTaskList_AddTail(s32 arg0, void *arg1, s32 arg2);
extern u8 D_00341ED0[] __attribute__((section(".data")));
extern s32 D_003877A8 __attribute__((section(".data")));

/* Returns the new task: the asm leaves BtlTaskList_AddTail's v0 untouched up to jr ra (callers 14C580 / 158AD8 keep it). */
s32 func_00182A80(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlTaskList_AddTail(D_003877A8, D_00341ED0, arg0);
    if (temp_v0 != NULL) {
        *(s8 *)((u8 *)temp_v0 + 1) = 0;
    }
    return (s32)temp_v0;
}
