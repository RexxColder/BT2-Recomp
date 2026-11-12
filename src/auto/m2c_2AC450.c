#include "m2c_macros.h"

M2C_UNK func_00255EA0();                            /* extern */
M2C_UNK func_00298158(M2C_UNK);                     /* extern */
extern void *D_003876A0;

void func_002AC450(void) {
    M2C_FIELD(D_003876A0, s64 *, 0x4D8) = 0;
    func_00298158(0);
    func_00255EA0();
    func_00298158(1);
}
