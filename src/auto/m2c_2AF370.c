#include "m2c_macros.h"

s32 func_002ADFD8();                                /* extern */
M2C_UNK func_002AF578(s32, M2C_UNK);                /* extern */
M2C_UNK func_002B1CA8(s32, M2C_UNK);                /* extern */
extern void *D_00387E18;

void func_002AF370(s32 arg0) {
    if (func_002ADFD8(arg0) != 0) {
        func_002AF578(arg0, 0x26);
    } else {
        func_002AF578(arg0, 0x1B);
    }
    func_002B1CA8(arg0, 8);
    M2C_FIELD(D_00387E18, s8 *, 9) = 1;
}
