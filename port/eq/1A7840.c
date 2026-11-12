#include "common.h"

void func_00129C28(void *arg0, s32 arg1);
f32 func_001A7818(f32 *arg0, f32 *arg1);
void BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);
extern u8 D_003426C8[] __attribute__((section(".data")));
extern s32 *gEftStruggle;

f32 func_001A7840(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x320];
    f32 lenA;
    f32 lenB;
    f32 ratio;

    __builtin_memset(sp, 0, 0x320);
    func_00129C28(sp, arg0);

    if (*(s32 *)arg1 != 0) {
        __builtin_memcpy(sp + 0x20, arg2, 0x180);
        __builtin_memcpy(sp + 0x1A0, arg1, 0x180);
    } else {
        __builtin_memcpy(sp + 0x20, arg1, 0x180);
        __builtin_memcpy(sp + 0x1A0, arg2, 0x180);
    }

    *(f32 *)(sp + 0x3C) = 1.0f;
    *(f32 *)(sp + 0x1BC) = 1.0f;
    lenA = __builtin_sqrtf(__builtin_fabsf(func_001A7818((f32 *)(sp + 0x1B0), (f32 *)(sp + 0x30))));
    lenB = __builtin_sqrtf(__builtin_fabsf(func_001A7818((f32 *)(sp + 0x30), (f32 *)(sp + 0x40))));

    ratio = lenB / lenA;
    *(f32 *)(sp + 0x10) = ratio;
    BtlTaskList_AddTail(*gEftStruggle, D_003426C8, sp);
    return *(f32 *)(sp + 0x10);
}
