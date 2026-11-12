#include "m2c_macros.h"

void *func_00211288(M2C_UNK);                       /* extern */
s32 func_00269A40(s32, M2C_UNK);                    /* extern */
M2C_UNK func_003126C8(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_002C3630 __attribute__((section(".data")));

void func_00210F30(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_v0;
    void *var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    temp_v0 = func_00269A40(M2C_FIELD(var_v0, s32 *, 0x1530), arg2);
    if (temp_v0 == 0) {
        func_003126C8(arg1, &D_002C3630);
        return;
    }
    func_003126C8(arg1, temp_v0 + 0x30);
}
