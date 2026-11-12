#include "m2c_macros.h"

M2C_UNK func_0026C1B0(s32);                         /* extern */
M2C_UNK func_0026DEF0(void *);                      /* extern */
M2C_UNK func_0026F770(s32);                         /* extern */
M2C_UNK func_0026FEE0(s32);                         /* extern */

void func_0026EA88(void *arg0) {
    void *temp_v1;

    M2C_FIELD(arg0, s32 *, 0x14) = 1;
    func_0026DEF0(M2C_FIELD(arg0, void **, 0x18));
    temp_v1 = M2C_FIELD(arg0, void **, 0x18);
    M2C_FIELD(temp_v1, u8 *, 0x11) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x11) | 2);
    func_0026FEE0(M2C_FIELD(arg0, s32 *, 0x1C));
    func_0026F770(M2C_FIELD(arg0, s32 *, 0x20));
    func_0026C1B0(M2C_FIELD(arg0, s32 *, 0x24));
}
