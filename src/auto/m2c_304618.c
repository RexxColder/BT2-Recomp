#include "m2c_macros.h"

M2C_UNK func_0030C840();                      /* extern */
M2C_UNK strcat();                    /* extern */
M2C_UNK strcpy();                        /* extern */

void func_00304618(s32 arg0, M2C_UNK arg1) {
    s32 sp[16];
    strcpy(sp, arg0);
    strcat(sp, arg1);
    func_0030C840(sp);
}
