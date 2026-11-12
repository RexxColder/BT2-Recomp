#include "m2c_macros.h"

M2C_UNK func_002D3DF0();                            /* extern */
M2C_UNK func_002D3E78(s32);                         /* extern */
s32 func_002D3F00(s32);                             /* extern */

s32 func_002D3DA8(s32 arg0) {
    s32 temp_s0;

    func_002D3DF0(arg0);
    temp_s0 = func_002D3F00(arg0);
    func_002D3E78(arg0);
    return temp_s0;
}
