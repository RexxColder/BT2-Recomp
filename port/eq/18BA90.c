#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00341F78[] __attribute__((section(".data")));
extern u8 *D_003877B4;

s32 func_0018BA90(s32 arg0) {
    if (D_003877B4 != NULL) {
        return BtlTaskList_AddTail(*(s32 *)(D_003877B4 + 0x7AF4), (s32)D_00341F78, arg0);
    }
    return 0;
}
