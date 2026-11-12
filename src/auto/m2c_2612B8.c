#include "m2c_macros.h"

s32 func_00261060(s32);                             /* extern */
M2C_UNK func_00265AC8(s32, M2C_UNK);                /* extern */
extern s32 D_003B2654 __attribute__((section(".data")));

void func_002612B8(s32 arg0, M2C_UNK arg1) {
    if (!(D_003B2654 & 0x100)) {
        func_00265AC8(func_00261060(arg0 & 0xFFFF), arg1);
    }
}
