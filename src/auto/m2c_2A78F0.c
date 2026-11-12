#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_002A3BB8(s32, s32);                    /* extern */

s32 func_002A78F0(s32 arg0) {
    s32 temp_v0;
    s32 size;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {
            size = Gsc_GetInt();   /* el guion siempre trae el 2.º operando: consumirlo igual */
            if (temp_v0 < 8) {
                func_002A3BB8(temp_v0, size);
            }
        }
    }
    return 1;
}
