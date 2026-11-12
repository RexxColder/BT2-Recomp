#include "m2c_macros.h"

M2C_UNK func_00105570();                            /* extern */
M2C_UNK func_001066B8(M2C_UNK);                     /* extern */
M2C_UNK func_0010AD18();                            /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 D_003876B4;

void func_00105698(void) {
    s32 temp_v0;

    temp_v0 = func_0028BAA8(0x114);
    D_003876B4 = temp_v0;
    memset(temp_v0, 0, 0x114);
    func_0010AD18();
    func_001066B8(0);
    func_00105570();
}
