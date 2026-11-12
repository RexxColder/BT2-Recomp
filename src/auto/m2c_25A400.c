#include "m2c_macros.h"

M2C_UNK func_0025A060(s32);                         /* extern */
M2C_UNK func_0025A310();                            /* extern */
M2C_UNK func_0025B5E8(s32, M2C_UNK *);              /* extern */
M2C_UNK func_0025BDD0(s32, M2C_UNK *, M2C_UNK *);   /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern M2C_UNK D_002C3630 __attribute__((section(".data")));
extern s32 D_00387A30;

void func_0025A400(void) {
    s32 temp_v0;

    temp_v0 = func_0028BAA8(0x320);
    D_00387A30 = temp_v0;
    memset(temp_v0, 0, 0x320);
    func_0025A060(D_00387A30);
    func_0025A310();
    func_0025BDD0(D_00387A30, &D_002C3630, &D_002C3630);
    func_0025B5E8(D_00387A30, &D_002C3630);
}
