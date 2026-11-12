#include "m2c_macros.h"

f32 Gsc_GetFloat();                                 /* extern */
s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002A3D90(f32, s32, s32);               /* extern */

s32 func_002A6708(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {
            temp_s0 = Gsc_GetInt() & 0xFF;
            func_002A3D90(Gsc_GetFloat(), temp_v0, temp_s0);
        }
    }
    return 1;
}
