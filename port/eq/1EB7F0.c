#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00343598[] __attribute__((section(".data")));
extern s32 *D_00387908;

s32 func_001EB7F0(s32 arg0) {
    if (D_00387908 != NULL) {
        return BtlTaskList_AddTail(D_00387908[0x204 / 4], (s32)D_00343598, arg0);
    }
    return 0;
}
