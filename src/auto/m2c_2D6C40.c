#include "m2c_macros.h"

M2C_UNK func_002D7308(s32);                         /* extern */
M2C_UNK func_002E0E08(s32);                         /* extern */
extern s32 D_00346EA0 __attribute__((section(".data")));

void func_002D6C40(void *arg0) {
    s32 temp_s0;

    if (arg0 != NULL) {
        temp_s0 = M2C_FIELD(arg0, s32 *, 0x30);
        M2C_FIELD(arg0, s32 *, 0) = 0;
        func_002D7308(M2C_FIELD(arg0, s32 *, 0x24));
        func_002E0E08(temp_s0);
        D_00346EA0 -= 1;
    }
}
