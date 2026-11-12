#include "common.h"

void func_003C2918(s32, s8);
extern s8 D_00421CA0[] __attribute__((section(".data")));

void func_003C2D38(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_003C2918(arg0, D_00421CA0[(arg1 * 42) + (arg2 * 14) + arg3]);
}
