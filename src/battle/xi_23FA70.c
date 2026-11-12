#include "m2c_macros.h"

s32 func_001F97A8(void *, void *);                  /* extern */

// Returns (field +0x78 of the object at +0x958 of arg0->+0x1530) / 30 plus func_001F97A8(arg0, that object).
s32 func_0023FA70(void *arg0) {
    void *temp_a1;
    s32 temp_s0;

    temp_a1 = M2C_FIELD(arg0, void **, 0x1530);
    temp_s0 = (s32) M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x958), s32 *, 0x78) / 30;
    return temp_s0 + func_001F97A8(arg0, temp_a1);
}
