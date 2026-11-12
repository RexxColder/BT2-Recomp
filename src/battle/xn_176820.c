#include "m2c_macros.h"

void func_0014E970(void *);                      /* extern */

void func_00176820(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    func_0014E970(temp_s0);
    M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x1E88), s32 *, 0x204) = 0;
}
