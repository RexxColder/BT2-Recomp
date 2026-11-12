#include "m2c_macros.h"

M2C_UNK func_002C0E10(void *, s32, s32);            /* extern */

/* Calls func_002C0E10 with the sub-object's word at +0x1F44 and flag 1; returns 0. */
s32 func_002C32F0(void *arg0) {
    func_002C0E10(arg0, M2C_FIELD(arg0, s32 *, 0x1F44), 1);
    return 0;
}
