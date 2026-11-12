#include "common.h"
extern u8 D_00388DC4[] __attribute__((section(".data")));

void func_002839B0(u32 arg0, s32 arg1) {
    if (arg0 < 8) {
        *(s32 *)(D_00388DC4 + arg0 * 0x30) = arg1;
    }
}
