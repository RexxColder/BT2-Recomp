#include "m2c_macros.h"

s32 func_001F9848(void *, void *);                  /* extern */

// Returns (field +0x8C of the object at +0x958 of arg0->+0x1530) / 30 plus func_001F9848(arg0, that object).
s32 func_0023FB90(void *arg0) {
    void *temp_a1;
    s32 temp_s0;

    temp_a1 = M2C_FIELD(arg0, void **, 0x1530);
    temp_s0 = (s32) M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x958), s32 *, 0x8C) / 30;
    return temp_s0 + func_001F9848(arg0, temp_a1);
}
