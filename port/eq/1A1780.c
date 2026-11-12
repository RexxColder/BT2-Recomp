#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003423E0 __attribute__((section(".data")));
extern s32 *D_00387818;

s32 func_001A1780(s32 arg0, s32 arg1) {
    s32 rec[8];

    rec[0] = arg0;
    func_003126C8((s32)&rec[4], arg1);
    return BtlTaskList_AddTail(*D_00387818, (s32)&D_003423E0, (s32)rec);
}
