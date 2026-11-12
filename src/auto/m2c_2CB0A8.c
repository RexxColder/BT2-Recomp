#include "m2c_macros.h"

M2C_UNK func_002C32B0();                      /* extern */
M2C_UNK func_002C32C8();                      /* extern */
M2C_UNK func_002CB140();  /* extern */
s32 func_002D07B0();                 /* extern */
s32 func_002D2268();                /* extern */

void *func_002CB0A8(void *arg0) {
    s32 sp[1];
    M2C_UNK sp4;
    void *sp8;

    func_002C32B0(sp);
    if (M2C_FIELD(arg0, s32 *, 0x48) != 4) {
        sp8 = NULL;
    } else {
        func_002CB140(arg0, &sp4, &sp8);
        if ((sp8 != NULL) && (func_002D07B0(arg0, 0xF) != 0)) {
            sp8 = (func_002D2268(arg0, M2C_FIELD(sp8, s32 *, 0x38), M2C_FIELD(sp8, s32 *, 0x3C)) == 0) ? NULL : sp8;
        }
    }
    func_002C32C8(sp);
    return sp8;
}
