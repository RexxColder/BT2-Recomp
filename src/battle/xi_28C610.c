#include "m2c_macros.h"

f32 Pad_StickToFloat(u8 raw, s32 deadzone);          /* extern */
s32 func_0028C520();                                /* extern */

// Passes its incoming arguments to func_0028C520, then tail-calls Pad_StickToFloat(result, arg2) (f32 in f0).
f32 func_0028C610(s32 arg0, s32 arg1, s32 arg2) {
    return Pad_StickToFloat(func_0028C520(arg0, arg1, arg2), arg2);
}
