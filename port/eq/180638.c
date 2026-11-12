#include "common.h"

extern s32 *D_00387798 __attribute__((section(".data")));

void func_00180638(u32 arg0) {
    u32 idx;
    idx = (arg0 < 3U) ? arg0 : 0U;
    D_00387798[idx] = 0;
}
