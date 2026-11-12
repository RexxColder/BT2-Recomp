#include "m2c_macros.h"

M2C_UNK func_00272E90();                            /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
extern void *D_003876A0;
extern s8 D_00387ABC;

void func_002738B8(void) {
    void *temp_s0;

    temp_s0 = D_003876A0;
    M2C_FIELD(temp_s0, s32 *, 8) = func_0028BAA8(0x4B0800);
    D_00387ABC = 0;
    func_00272E90();
}
