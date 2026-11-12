#include "m2c_macros.h"

M2C_UNK sceVu0CopyMatrix(s32);                      /* extern */
M2C_UNK sceVu0InversMatrix(s32, s32);               /* extern */

void func_00260B58(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0xA00;
    sceVu0CopyMatrix(temp_s1);
    sceVu0InversMatrix(arg0 + 0xA40, temp_s1);
    M2C_FIELD(arg0, s8 *, 0xAEC) = 0;
}
