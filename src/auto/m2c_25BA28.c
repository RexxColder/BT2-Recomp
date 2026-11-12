#include "m2c_macros.h"

s32 func_00100ED0(s32, M2C_UNK, s32);               /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
extern s32 D_00388A00 __attribute__((section(".data")));

void func_0025BA28(s32 arg0, s32 arg1) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s0 = &D_00388A00;
    var_s1 = arg1 & 0xFFFF;
    var_s2 = arg0 & 0xFF;
    if (D_00388A00 != 0) {
        func_0028BB60(D_00388A00);
        D_00388A00 = 0;
    }
    D_00388A00 = func_00100ED0(var_s1, 0, var_s2 != 0);
}
