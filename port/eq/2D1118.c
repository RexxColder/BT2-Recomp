#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
extern u8 D_00346DD8[] __attribute__((section(".data")));

void func_002D1118(s32 arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    if (func_002D07B0(arg0, 0x47) == 1) {
        *arg2 = *(s32 *)(arg1 + 0x2A8) - *(s32 *)(arg1 + 0x2D0);
        *arg3 = *(s32 *)(D_00346DD8 + 0x8);
        return;
    }
    *arg2 = *(s32 *)(arg1 + 0x2DC) - *(s32 *)(arg1 + 0x2D0);
    *arg3 = *(s32 *)(arg1 + 0x2E0);
}
