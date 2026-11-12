#include "m2c_macros.h"

M2C_UNK func_002B6E50();                 /* extern */
M2C_UNK func_00325830(); /* extern */
extern M2C_UNK D_00378DA0 __attribute__((section(".data")));

void func_002B7658(s32 arg0, M2C_UNK arg1, s32 arg2) {
    s32 sp[8];
    func_00325830(sp, &D_00378DA0, arg1, (u32) (arg2 + 0x7FF) >> 0xB);
    func_002B6E50(arg0, sp);
}
