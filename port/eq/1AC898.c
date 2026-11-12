#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2, s64 arg3);
extern u8 D_00342758[] __attribute__((section(".data")));
extern u8 *D_0038784C;

void func_001AC898(u8 *arg0) {
    s64 sp[8];
    s32 i;
    u8 t3;

    if (D_0038784C != NULL) {
        for (i = 0; i < 8; i++) {
            sp[i] = *(s64 *)(arg0 + 8 * i);
        }
        t3 = ((u8 *)sp)[0x1A];
        if (t3 == 0xE) {
            BtlTaskList_AddTail(*(s32 *)D_0038784C, D_00342758, sp, *(s64 *)(arg0 + 0x30));
        } else if (t3 == 0xF) {
            BtlTaskList_AddTail(*(s32 *)D_0038784C, D_00342758, sp, *(s64 *)(arg0 + 0x30));
            ((s32 (*)(s32, void *, void *))BtlTaskList_AddTail)(*(s32 *)D_0038784C, D_00342758, sp);
        }
    }
}
