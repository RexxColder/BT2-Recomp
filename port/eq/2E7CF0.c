#include "common.h"

extern u8 D_00347BEC[] __attribute__((section(".data")));
extern u8 D_00347BEE[] __attribute__((section(".data")));
extern u8 D_00347BF0[] __attribute__((section(".data")));
s32 func_002E70B0(u8 *a0, s32 a1, u8 *a2, u8 *a3, u8 *a4);
u32 strlen(u8 *s);

s32 func_002E7CF0(u8 *arg0) {
    return func_002E70B0(arg0, strlen(arg0), D_00347BEC, D_00347BEE, D_00347BF0);
}
