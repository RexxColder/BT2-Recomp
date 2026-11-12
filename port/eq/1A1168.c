#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00342380[] __attribute__((section(".data")));
extern u8 *D_0038780C;
extern s32 D_00387810;

s32 func_001A1168(u8 *arg0) {
    u64 sp[8];
    s32 idx;
    s32 temp_a1;
    s32 var_v0;

    sp[0] = *(u64 *)(arg0 + 0x00);
    sp[1] = *(u64 *)(arg0 + 0x08);
    sp[2] = *(u64 *)(arg0 + 0x10);
    sp[3] = *(u64 *)(arg0 + 0x18);
    sp[4] = *(u64 *)(arg0 + 0x20);
    sp[5] = *(u64 *)(arg0 + 0x28);
    sp[6] = *(u64 *)(arg0 + 0x30);
    sp[7] = *(u64 *)(arg0 + 0x38);
    idx = *(s32 *)arg0;

    var_v0 = 0;
    if (*(s32 *)(D_0038780C + idx * 4) == 0) {
        var_v0 = BtlTaskList_AddTail(D_00387810, (s32)D_00342380, (s32)sp);
        temp_a1 = var_v0;
        if (temp_a1 != 0) {
            var_v0 = 1;
            *(s32 *)(D_0038780C + idx * 4) = temp_a1;
        }
    }
    return var_v0;
}
