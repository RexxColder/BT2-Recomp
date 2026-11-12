#include "m2c_macros.h"

M2C_UNK func_002C2710(void *);                      /* extern */
M2C_UNK func_002DA3A8(s32, s32, s32);               /* extern */

void func_002C1A78(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_s0;

    temp_s0 = (arg1 < 0x801) ? arg1 : 0x800;
    func_002DA3A8(arg2 + 0x94, arg0, temp_s0);
    M2C_FIELD(arg2, s32 *, 0x90) = temp_s0;
    func_002C2710(arg2);
}
