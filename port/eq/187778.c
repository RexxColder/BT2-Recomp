#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00341F38[] __attribute__((section(".data")));
extern u8 *D_003877B0;

s32 func_00187778(s32 arg0) {
    if (D_003877B0 != NULL) {
        return BtlTaskList_AddTail(*(s32 *)(D_003877B0 + 0x79E4), (s32)D_00341F38, arg0);
    }
    return 0;
}
