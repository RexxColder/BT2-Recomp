#include "common.h"

void func_002CCDF8(s32 arg0, s32 arg1);

extern s32 D_00346E6C __attribute__((section(".data")));

void func_002CCDD0(s32 arg0, s32 arg1) {
    func_002CCDF8(arg0, arg1);
    D_00346E6C = 0;
}
