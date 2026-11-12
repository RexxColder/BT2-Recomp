#include "m2c_macros.h"

s32 func_002C5FC0(s32);                             /* extern */
s32 func_002C6028(s32);                             /* extern */
s32 func_002CABF8();                                /* extern */

s32 func_002C5F60(s32 arg0) {
    if ((func_002CABF8(arg0) != 0) || ((func_002C5FC0(arg0) != 0) && (func_002C6028(arg0) != 0))) {
        return 1;
    }
    return 0;
}
