#include "common.h"

extern s32 D_00346EA8[] __attribute__((section(".data")));

void func_002D6A10(s32 arg0, s32 arg1) {
    D_00346EA8[1] = arg1;
    D_00346EA8[0] = arg0;
}
