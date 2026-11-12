#include "m2c_macros.h"

M2C_UNK func_00123BE0();                            /* extern */
extern void *D_003876A0;

void func_0011E7F8(void) {
    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2)) {
        func_00123BE0();
    }
}
