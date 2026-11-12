#include "m2c_macros.h"

M2C_UNK func_001014E8(s32);                         /* extern */
M2C_UNK func_00101508(s32);                         /* extern */
s32 func_002494C0(f32);                             /* extern */

void func_00249510(s32 arg0, s32 arg1) {
    func_00101508(arg0 + 3);
    func_001014E8(func_002494C0((f32) arg1));
}
