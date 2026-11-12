#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, u8 *arg1, s32 *arg2);
s32 func_0019C270(s32 arg0, s32 arg1);
void func_0019C1D8(u8 *arg0, u8 *arg1, s32 arg2);
extern u8 D_00342270[] __attribute__((section(".data")));
extern u8 *D_003877EC;

void func_0019C2C8(s32 arg0, s32 arg1) {
    s32 sp[3];

    sp[0] = 0;
    sp[1] = arg0;
    sp[2] = arg1;
    if (D_003877EC != NULL) {
        s32 t;

        sp[0] = *(s32 *)D_003877EC;
        t = func_0019C270(BtlTaskList_AddTail(*(s32 *)(D_003877EC + 0x27C), D_00342270, sp), arg0);
        if (t != 0) {
            func_0019C1D8(D_003877EC + 0x238, D_003877EC + 0x23C, t);
        }
    }
}
