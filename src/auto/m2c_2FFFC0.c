#include "m2c_macros.h"

M2C_UNK func_002F21A0(s32);                         /* extern */
M2C_UNK func_002FFE88(void *);                      /* extern */
M2C_UNK func_003007F8(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037E948 __attribute__((section(".data")));

void func_002FFFC0(void *arg0) {
    s32 temp_a0;

    if (arg0 == NULL) {
        func_003007F8(&D_0037E948);
        return;
    }
    if (M2C_FIELD(arg0, s8 *, 1) != 0) {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x28);
        M2C_FIELD(arg0, s8 *, 1) = 0;
        if ((temp_a0 != 0) && (M2C_FIELD(arg0, s8 *, 2) == 1)) {
            func_002F21A0(temp_a0);
            M2C_FIELD(arg0, s8 *, 2) = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x2C) = 0;
        func_002FFE88(arg0);
        M2C_FIELD(arg0, s32 *, 0x34) = 0;
    }
}
