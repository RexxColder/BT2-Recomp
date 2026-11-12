#include "m2c_macros.h"

void *func_00101A88();                              /* extern */

/* Reads a record from func_00101A88: *arg1 (a1) = flag (+0x1C5 != 1), *arg2 (a2) = word +0x10. arg0 is unused. */
void func_00101F18(void *unused, s8 *arg1, s32 *arg2) {
    void *temp_v0;

    temp_v0 = func_00101A88(unused);
    *arg1 = M2C_FIELD(temp_v0, u8 *, 0x1C5) != 1;
    *arg2 = M2C_FIELD(temp_v0, s32 *, 0x10);
}
