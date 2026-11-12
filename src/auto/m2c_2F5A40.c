#include "m2c_macros.h"

M2C_UNK func_002E93F0();                            /* extern */
M2C_UNK func_002E93F8();                            /* extern */
f32 func_002F5A80(s32);                             /* extern */

f32 func_002F5A40(s32 arg0) {
    f32 temp_f20;

    func_002E93F0();
    temp_f20 = func_002F5A80(arg0);
    func_002E93F8();
    return temp_f20;
}
