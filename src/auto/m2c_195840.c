#include "m2c_macros.h"

s32 func_00195A58();                                /* extern */

void func_00195840(void *arg0) {
    void *temp_v1;

    if (func_00195A58(arg0) != 0) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_v1, s32 *, 0xB70) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xB70) | 8);
    }
}
