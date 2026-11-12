#include "m2c_macros.h"

f32 func_00209B88(s32);                             /* extern */
s32 func_0020A440();                                /* extern */

f32 func_001146E0(s32 arg0) {
    if (func_0020A440(arg0) != 0) {
        return -func_00209B88(arg0);
    }
    return 0.0f;
}
