#include "m2c_macros.h"

s32 adxt_GetSfreq(s32);                             /* extern */
M2C_UNK func_002E93F0();                            /* extern */
M2C_UNK func_002E93F8();                            /* extern */

s32 func_002F4CE0(s32 arg0) {
    s32 temp_s0;

    func_002E93F0();
    temp_s0 = adxt_GetSfreq(arg0);
    func_002E93F8();
    return temp_s0;
}
