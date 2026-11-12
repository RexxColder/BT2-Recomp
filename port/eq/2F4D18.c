#include "common.h"

/* 0x002F4D18 adxt_GetFmtBps: a0 == 0 -> func_002EA050(error string D_0037C830), return -1;
 * (s8)a0[1] < 2 -> 0; else tail func_002F1540(*(a0 + 4)). */
extern u8 D_0037C830[] __attribute__((section(".data")));
s32 func_002EA050();
s32 func_002F1540(s32 arg0);

s32 func_002F4D18(u8 *a0) {
    if (a0 == 0) {
        func_002EA050((s32)D_0037C830);
        return -1;
    }
    if ((s8)a0[1] < 2) {
        return 0;
    }
    return func_002F1540(*(s32 *)(a0 + 4));
}
