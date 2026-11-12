#include "m2c_macros.h"

M2C_UNK func_002F1F10(void *, s32);                     /* extern */

void func_002F3190(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    func_002F1F10(arg0, 0);
}
