#include "m2c_macros.h"
s32 func_002C2FF0(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_002C3138(); /* extern */
s32 func_002C3210();                                /* extern */
extern M2C_UNK D_00346DC4 __attribute__((section(".data")));

/* With a NULL object, reports to D_00346DC4; otherwise calls func_002C3138 on the sub-object at +0x9F8,
   or sends an error command when func_002C3210 says so. Returns 0 on the normal paths. */
s32 func_002C30A0(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (arg0 == NULL) {
        func_002C3138(&D_00346DC4, arg1, arg2);
    } else if (func_002C3210() != 0) {
        return func_002C2FF0(0, 0xFF000101);
    } else {
        func_002C3138((u8 *) arg0 + 0x9F8, arg1, arg2);
    }
    return 0;
}
