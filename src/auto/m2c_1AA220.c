#include "m2c_macros.h"

s32 func_00126560();                                /* extern */
M2C_UNK func_001AA1F0();                            /* extern */
extern void *D_00387840;

void func_001AA220(void) {
    if ((func_00126560() != 0) && (D_00387840 != NULL)) {
        M2C_FIELD(D_00387840, s8 *, 0x1091) = 1;
        func_001AA1F0();
    }
}
