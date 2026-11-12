#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00342350[] __attribute__((section(".data")));
extern s32 *D_00387808;

void func_001A0B50(s32 arg0) {
    s32 sp[4];

    if (D_00387808 != NULL) {
        sp[0] = arg0;
        D_00387808[0x5B0 / 4] = BtlTaskList_AddTail(D_00387808[0], (s32)D_00342350, (s32)sp);
    }
}
