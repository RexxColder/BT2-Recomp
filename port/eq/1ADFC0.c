#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4);
extern s32 D_00387850;
extern s32 D_00387854;
extern u8 D_00342788[] __attribute__((section(".data")));

s32 func_001ADFC0(u8 *arg0) {
    s64 sp[4];
    s32 s0;
    s32 v;

    if (arg0 == NULL) {
        return 0;
    }
    s0 = *(s32 *)(arg0 + 0x10) * 4 + 0x5A0;
    if (*(s32 *)(D_00387850 + s0 + 8) != 0) {
        return 0;
    }
    sp[0] = *(s64 *)(arg0 + 0x00);
    sp[1] = *(s64 *)(arg0 + 0x08);
    sp[2] = *(s64 *)(arg0 + 0x10);
    sp[3] = *(s64 *)(arg0 + 0x18);
    v = BtlTaskList_AddTail(D_00387854, (s32)D_00342788, (s32)sp, *(s64 *)(arg0 + 0x00), *(s64 *)(arg0 + 0x18));
    *(s32 *)(D_00387850 + s0 + 8) = v;
    return 1;
}
