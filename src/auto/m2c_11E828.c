#include "m2c_macros.h"

M2C_UNK func_0011FE00(s32);                         /* extern */
s32 func_00125FF0();                                /* extern */
extern void *D_003876A0;

void func_0011E828(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2) {
        return;
    }
    func_0011FE00(func_00125FF0(r_a0));
}
