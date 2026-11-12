#include "m2c_macros.h"

M2C_UNK func_001C7A40();                            /* extern */
extern void *D_003876A0;

void func_001C7828(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 0x100)) {
        func_001C7A40(r_a0);
    }
}
