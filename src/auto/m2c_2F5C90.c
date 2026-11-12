#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
s32 func_002F45C8();                                /* extern */
extern M2C_UNK D_0037CBF8 __attribute__((section(".data")));

s32 func_002F5C90(s32 arg0) {
    s32 temp_v0;
    s32 var_v0;

    if (arg0 == 0) {
        func_002EA050(&D_0037CBF8);
        return -1;
    }
    temp_v0 = func_002F45C8();
    if ((temp_v0 >= 5) || (var_v0 = 0, (temp_v0 <= 0))) {
        var_v0 = 1;
    }
    return var_v0;
}
