#include "common.h"

void func_002EA050(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
void func_002EA0C8(u8 *arg0, s32 arg1);
s32 func_002FFC78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
extern u8 D_0037C2E0[] __attribute__((section(".data")));
extern u8 D_0037C310[] __attribute__((section(".data")));

void func_002ED5A0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == NULL) {
        func_002EA050(D_0037C2E0, arg1, 0, arg2, arg3);
        return;
    }
    if (func_002FFC78(*(s32 *)(arg0 + 0x94), arg1, 0, arg2, arg3) < 0) {
        func_002EA0C8(D_0037C310, arg1);
    }
}
