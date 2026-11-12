#include "m2c_macros.h"

M2C_UNK func_002E7538(s32);                         /* extern */
M2C_UNK func_002E93C0();                            /* extern */
M2C_UNK func_002E93D8();                            /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_002F0328(void *arg0) {
    s32 temp_v0;

    if (arg0 != NULL) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 4);
        if (temp_v0 != 0) {
            M2C_FIELD(arg0, s32 *, 4) = 0;
            func_002E7538(temp_v0);
        }
        func_002E93C0();
        memset(arg0, 0, 0xAC);
        func_002E93D8();
    }
}
