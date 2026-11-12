#include "m2c_macros.h"

M2C_UNK func_001EC818(void *, s32);                         /* extern */
M2C_UNK func_001ECF40(void *, s32);                         /* extern */

// Masks arg1 to a byte; calls func_001EC818 if field 0x68 has bit 8, else func_001ECF40, both with (arg0, value).
void func_001EC488(void *arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = arg1 & 0xFF;
    if (M2C_FIELD(arg0, s32 *, 0x68) & 8) {
        func_001EC818(arg0, temp_v1);
        return;
    }
    func_001ECF40(arg0, temp_v1);
}
