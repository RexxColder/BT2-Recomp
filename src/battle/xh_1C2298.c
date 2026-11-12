#include "m2c_macros.h"

M2C_UNK func_00129AB0(s32);                         /* extern */
M2C_UNK func_001C2158(s32, M2C_UNK);                /* extern */
M2C_UNK memset(void *, s32, s32);

// Clears 0xF0 bytes at arg0, calls func_001C2158(arg0,2), then func_00129AB0 on arg0+0xE0.
void func_001C2298(s32 arg0) {
    memset(arg0, 0, 0xF0);
    func_001C2158(arg0, 2);
    func_00129AB0(arg0 + 0xE0);
}
