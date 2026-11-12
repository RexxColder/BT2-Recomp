#include "common.h"

s32 func_002B8280(s32 arg0);
s32 Rand_Range(void *range, s32 arg1);
s32 func_00300720(s32 arg0, s32 arg1);
extern u8 D_00379B58[] __attribute__((section(".data")));

s32 func_002BAD68(s32 arg0, s32 arg1) {
    if (func_002B8280(arg0) != 1) {
        return Rand_Range(D_00379B58, arg1);
    }
    return func_00300720(*(s32 *)((u8 *)arg0 + 0x48), arg1);
}
