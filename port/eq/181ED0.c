#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void *memcpy(void *dst, void *src, u32 n);
extern u8 D_00341EA0[] __attribute__((section(".data")));
extern s32 *D_003877A0 __attribute__((section(".data")));

s32 func_00181ED0(void *arg0) {
    u8 sp[0x50];
    s32 var_v0;

    var_v0 = 0;
    if (D_003877A0 != NULL) {
        memcpy(sp, arg0, 0x50);
        var_v0 = BtlTaskList_AddTail(*D_003877A0, (s32) D_00341EA0, (s32) sp, (s32) D_003877A0) != 0;
    }
    return var_v0;
}
