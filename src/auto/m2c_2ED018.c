#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
s32 func_002F2D70();                                /* extern */
extern M2C_UNK D_0037C200 __attribute__((section(".data")));

s32 func_002ED018(s32 arg0) {
    if (arg0 == 0) {
        func_002EA050(&D_0037C200);
        return 0;
    }
    return func_002F2D70();
}
