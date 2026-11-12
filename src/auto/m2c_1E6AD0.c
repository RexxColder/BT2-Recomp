#include "m2c_macros.h"

M2C_UNK func_001E4C80(s32, s32, s32);               /* extern */

void func_001E6AD0(void *arg0) {
    s32 temp_a1;
    void *temp_a2;

    temp_a2 = arg0 + 0xC;
    temp_a1 = M2C_FIELD(arg0, s32 *, 8);
    switch (temp_a1) {                              /* irregular */
    case 0:
        func_001E4C80(0, M2C_FIELD(arg0, s32 *, 0x40), M2C_FIELD(temp_a2, s32 *, 0x10));
        return;
    case 1:
        func_001E4C80(M2C_FIELD(arg0, s32 *, 0x44), 0, M2C_FIELD(temp_a2, s32 *, 0x10));
        return;
    }
}
