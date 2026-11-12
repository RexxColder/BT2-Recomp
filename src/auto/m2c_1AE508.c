#include "m2c_macros.h"

void func_001AE508(void *arg0, void *arg1) {
    void *temp_v0;

    if (arg0 != NULL) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(arg1, f32 *, 0) = (f32) M2C_FIELD(temp_v0, f32 *, 0);
        M2C_FIELD(arg1, f32 *, 4) = (f32) M2C_FIELD(temp_v0, f32 *, 4);
        M2C_FIELD(arg1, f32 *, 8) = (f32) M2C_FIELD(temp_v0, f32 *, 8);
        M2C_FIELD(arg1, f32 *, 0xC) = (f32) M2C_FIELD(temp_v0, f32 *, 0xC);
    }
}
