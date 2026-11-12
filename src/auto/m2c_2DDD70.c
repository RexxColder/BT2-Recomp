#include "m2c_macros.h"

M2C_UNK func_002DDDC0(M2C_UNK *);                   /* extern */
extern M2C_UNK D_00347608 __attribute__((section(".data")));

s32 func_002DDD70(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        func_002DDDC0(&D_00347608);
    } else {
        func_002DDDC0(arg0 + 0x250);
    }
    return arg1;
}
