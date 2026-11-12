#include "m2c_macros.h"

s32 func_00126560();                                /* extern */
extern s32 D_00388728 __attribute__((section(".data")));

/* Stores arg2 into the 6-column table at D_00388728 when func_00126560 is nonzero. */
void func_00148A80(s32 arg0, s32 arg1, s32 arg2) {
    if (func_00126560() != 0) {
        *(&D_00388728 + ((arg0 * 6) + arg1)) = arg2;
    }
}
