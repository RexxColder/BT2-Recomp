#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
M2C_UNK func_002B7138(void *);                      /* extern */
s32 func_002B8280();                                /* extern */
M2C_UNK func_002BB418(void *, M2C_UNK);             /* extern */
M2C_UNK func_002FFF90(s32);                         /* extern */
extern M2C_UNK D_00378C98 __attribute__((section(".data")));

void func_002B7228(void *arg0) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00378C98);
        return;
    }
    func_002B7138(arg0);
    func_002BB418(arg0, 0);
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    func_002FFF90(M2C_FIELD(arg0, s32 *, 0x48));
}
