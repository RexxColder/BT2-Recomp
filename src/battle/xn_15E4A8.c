#include "m2c_macros.h"
void func_0014E970(void *);
void func_0015E4A8(void *arg0) {
    s32 *temp_v0;
    void *temp_s0;
    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    func_0014E970(temp_s0);
    temp_v0 = M2C_FIELD(temp_s0, s32 **, 0x1E84);
    M2C_FIELD(temp_v0, s32 *, 0x204) = 0;
}
