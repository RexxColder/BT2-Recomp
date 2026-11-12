#include "m2c_macros.h"

s32 func_00202E60(void *, s32);                        /* extern */
M2C_UNK func_002031E0(void *);                      /* extern */

// Calls func_00202E60 with the object and field 0x118C; if zero, or if field 0x118C equals 0x1180, calls func_002031E0; returns field 0x118C.
s32 func_00203188(void *arg0) {
    if (func_00202E60(arg0, M2C_FIELD(arg0, s32 *, 0x118C)) == 0) {
        func_002031E0(arg0);
    }
    if (M2C_FIELD(arg0, s32 *, 0x118C) == M2C_FIELD(arg0, s32 *, 0x1180)) {
        func_002031E0(arg0);
    }
    return M2C_FIELD(arg0, s32 *, 0x118C);
}
