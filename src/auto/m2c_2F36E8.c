#include "m2c_macros.h"

M2C_UNK func_002ED878();                 /* extern */
M2C_UNK func_00325830(); /* extern */
extern M2C_UNK D_0037C6A8 __attribute__((section(".data")));

void func_002F36E8(s32 arg0, M2C_UNK arg1, s32 arg2) {
    s32 sp[8];
    func_00325830(sp, &D_0037C6A8, arg1, (u32) (arg2 + 0x7FF) >> 0xB);
    func_002ED878(arg0, sp);
}
