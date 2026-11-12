#include "common.h"

void func_002B3C80(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 Rand_Range(s32 arg0);
extern u8 D_00377F90[] __attribute__((section(".data")));

void func_002B3D68(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v1 = arg0 + 0x16C;

    if (arg1 == 0) {
        *(s32 *)(v1 + 0x8) = 0;
        *(s32 *)(arg0 + 0x178) = arg0 + 0x160;
        *(s32 *)(v1 + 0x0) = 0;
        *(s32 *)(v1 + 0x4) = 0;
        func_002B3C80(arg0, arg1, arg2, arg3);
        return;
    }
    if (arg2 >= (*(s32 *)(arg0 + 0x18) + 4) * arg3) {
        *(s32 *)(v1 + 0x0) = arg1;
        *(s32 *)(v1 + 0x4) = arg2;
        *(s32 *)(v1 + 0x8) = arg3;
        *(s32 *)(arg0 + 0x178) = v1;
        func_002B3C80(arg0, arg1, arg2, arg3);
        return;
    }
    Rand_Range((s32)D_00377F90);
}
