#include "m2c_macros.h"

M2C_UNK func_0011FA50();                            /* extern */
M2C_UNK func_00123BE0();                            /* extern */
extern void *D_003876A0;

void func_0011E688(void) {
    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2) {
        return;
    }
    func_0011FA50();
    func_00123BE0();
}
