#include "m2c_macros.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, s32 arg2);
extern u8 D_00341FE8 __attribute__((section(".data")));
extern u8 *D_003877BC;

s32 func_00190510(s32 arg0) {
    if (D_003877BC != NULL && arg0 != 0) {
        return BtlTaskList_AddTail(*(s32 *)(D_003877BC + 0x5588), &D_00341FE8, arg0);
    }
    return 0;
}
