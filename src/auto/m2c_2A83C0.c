#include "m2c_macros.h"

s8 Gsc_GetInt();                                    /* extern */
void *func_002A3DB8(s8);                            /* extern */

s32 func_002A83C0(s32 arg0) {
    s8 temp_v0;
    void *temp_s0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {
            temp_s0 = func_002A3DB8(temp_v0);
            M2C_FIELD(temp_s0, s8 *, 0x18) = Gsc_GetInt();
        }
    }
    return 1;
}
