#include "m2c_macros.h"

void func_001F9A20(s32, s32);                    /* extern */
void func_0025FA60(s32);                         /* extern */

void func_001F9D10(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x8EC) != arg1) {
        func_0025FA60(M2C_FIELD(arg0, s32 *, 0x152C), arg1);
        func_001F9A20(M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0xBFC), arg1);
    }
    M2C_FIELD(arg0, s32 *, 0x8EC) = arg1;
}
