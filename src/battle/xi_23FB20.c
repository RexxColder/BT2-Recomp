#include "m2c_macros.h"

s32 func_00203C58(void *, s64);                     /* extern */

// Returns the word at +0x7C of the object at +0x958 of arg0->+0x1530, or 0 if func_00203C58(arg0, 0x8000) is nonzero.
s32 func_0023FB20(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), void **, 0x958), s32 *, 0x7C);
    return (func_00203C58(arg0, 0x8000) != 0) ? 0 : temp_s0;
}
