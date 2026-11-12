#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003423B0[] __attribute__((section(".data")));
extern s32 *D_00387814;

void func_001A1748(s32 arg0) {
    s32 sp[4];

    if (D_00387814 != NULL) {
        sp[0] = arg0;
        BtlTaskList_AddTail(*D_00387814, (s32)D_003423B0, (s32)sp);
    }
}
