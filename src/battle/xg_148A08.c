#include "m2c_macros.h"

s32 func_00126560();                                /* extern */
s32 func_00208738(s32, s32);                        /* extern */
extern s32 D_00388728 __attribute__((section(".data")));

/* Looks up a word in the 6-column table at D_00388728 when func_00126560 is nonzero, else calls func_00208738. */
s32 func_00148A08(s32 arg0, s32 arg1) {
    if (func_00126560() != 0) {
        return *(&D_00388728 + ((arg0 * 6) + arg1));
    }
    return func_00208738(arg0, arg1);
}
