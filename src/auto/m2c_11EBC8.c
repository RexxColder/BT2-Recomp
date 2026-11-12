#include "m2c_macros.h"

f32 func_0011EB88(s32);                             /* extern */
f32 func_0011EBA8();                                /* extern */

f32 func_0011EBC8(s32 arg0) {
    f32 temp_f20;

    temp_f20 = func_0011EBA8(arg0);
    return temp_f20 / func_0011EB88(arg0);
}
