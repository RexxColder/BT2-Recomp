#include "m2c_macros.h"

M2C_UNK func_002FC550(M2C_UNK);                     /* extern */
s32 sceCdSync(M2C_UNK);                             /* extern */

s32 func_002FC330(void) {
    s32 temp_s0;

    func_002FC550(0x2300);
    temp_s0 = sceCdSync(1);
    func_002FC550(0x2301);
    return temp_s0;
}
