#include "m2c_macros.h"

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern M2C_UNK func_00111690 __attribute__((section(".data")));

void func_00111A98(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    memset(arg0 + 0x74, 0, 0x30);
    M2C_FIELD(arg0, s32 *, 0x74) = arg3;
    M2C_FIELD(arg0, s32 *, 0x7C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x80) = arg2;
    M2C_FIELD(arg0, M2C_UNK **, 0xA4) = &func_00111690;
}
