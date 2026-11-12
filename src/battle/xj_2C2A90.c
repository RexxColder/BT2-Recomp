#include "m2c_macros.h"

s32 func_002C2CF8();       /* extern */
extern M2C_UNK func_002D5268 __attribute__((section(".data")));
extern M2C_UNK func_002D52D8 __attribute__((section(".data")));
extern M2C_UNK func_002D5358 __attribute__((section(".data")));
extern M2C_UNK func_002D53C8 __attribute__((section(".data")));

void func_002C2A90(M2C_UNK *arg0, s32 arg1, void *arg2) {
    if (arg1 != 0) {
        M2C_FIELD(arg2, s32 *, 0) = func_002C2CF8(arg0, arg1, &func_002D5268);
        M2C_FIELD(arg2, s32 *, 4) = func_002C2CF8(arg0, arg1, &func_002D52D8);
        M2C_FIELD(arg2, s32 *, 8) = func_002C2CF8(arg0, arg1, &func_002D5358);
        M2C_FIELD(arg2, s32 *, 0xC) = func_002C2CF8(arg0, arg1, &func_002D53C8);
    }
}
