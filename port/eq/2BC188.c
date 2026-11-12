#include "common.h"

extern u8 D_00346BF0 __attribute__((section(".data")));

void func_002BC188(s32 arg0, s32 arg1) {
    *(s32 *)(&D_00346BF0 + arg1 * 8) = arg0;
}
