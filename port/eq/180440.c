#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00341E40[] __attribute__((section(".data")));
extern u8 *D_00387798;

void func_00180440(u8 *arg0, u8 *arg1) {
    s32 v;
    u16 idx;

    *(s32 *)(arg1 + 0x24) = *(s32 *)(arg0 + 0x7C);
    v = BtlTaskList_AddTail(*(s32 *)(D_00387798 + 0xC), (s32)D_00341E40, (s32)arg1);
    if (v != 0) {
        idx = *(u16 *)((u8 *)v + 2);
        *(s32 *)(arg0 + idx * 4) = v;
    }
}
