#include "m2c_macros.h"

M2C_UNK func_002C32B0();                      /* extern */
M2C_UNK func_002C32C8();                      /* extern */

void func_002C0598(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 sp[4];
    s32 *var_s1;
    s32 *var_s2;
    void *var_s0;

    var_s1 = arg2;
    var_s0 = arg0 + (arg1 * 0x74);
    var_s0 += 0x1338;
    var_s2 = arg3;
    func_002C32B0(sp, arg1, arg2, arg3);
    *var_s1 = M2C_FIELD(var_s0, s32 *, 0);
    *var_s2 = M2C_FIELD(var_s0, s32 *, 4);
    func_002C32C8(sp);
}
