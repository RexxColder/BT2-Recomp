#include "m2c_macros.h"

M2C_UNK func_002CFA30();                            /* extern */
M2C_UNK func_002D0290(void *);                      /* extern */

void func_002CF9E8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x36B0) == 0) {
        return;
    }
    func_002CFA30(arg0);
    func_002D0290(arg0);
}
