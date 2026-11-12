#include "m2c_macros.h"

M2C_UNK func_00103000(M2C_UNK);                     /* extern */
M2C_UNK func_002AC308();                            /* extern */
M2C_UNK func_002AC450();                            /* extern */
M2C_UNK func_002AC4A0();                            /* extern */
s32 func_002AC9A8();                                /* extern */

s32 func_002AC520(void) {
loop_1:
    func_002AC308();
    if (func_002AC9A8() == 0) {
        func_002AC450();
        func_00103000(0);
        if (func_002AC9A8() == 0) {
            func_002AC4A0();
            goto loop_1;
        }
    }
    return 1;
}
