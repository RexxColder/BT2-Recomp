#include "m2c_macros.h"

s32 func_002F98E0();                                /* extern */
s32 func_002FB108(s32);                             /* extern */
M2C_UNK func_00325830(M2C_UNK, M2C_UNK *, s32, M2C_UNK *); /* extern */
M2C_UNK strcpy(M2C_UNK *, M2C_UNK);                 /* extern */
extern M2C_UNK D_0037DD50 __attribute__((section(".data")));
extern M2C_UNK D_0039DB48 __attribute__((section(".data")));

void func_002FB158(s32 arg0, M2C_UNK arg1) {
    s32 var_s0;

    var_s0 = arg0;
    if (var_s0 == 0) {
        var_s0 = func_002F98E0();
    }
    if (func_002FB108(var_s0) == 1) {
        strcpy(&D_0039DB48, arg1);
        func_00325830(arg1, &D_0037DD50, var_s0, &D_0039DB48);
    }
}
