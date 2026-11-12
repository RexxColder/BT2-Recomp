#include "m2c_macros.h"

s32 func_00195A58();                                /* extern */

void func_00195980(void *arg0) {
    s32 temp_v0;
    void *temp_a0;

    if (func_00195A58(arg0) != 0) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        temp_v0 = M2C_FIELD(temp_a0, s32 *, 0xB70);
        if (!(temp_v0 & 0x200)) {
            M2C_FIELD(temp_a0, s32 *, 0xB70) = (s32) (temp_v0 | 0x280);
        }
    }
}
