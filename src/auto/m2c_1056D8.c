#include "m2c_macros.h"

M2C_UNK func_00101700(M2C_UNK);                     /* extern */
M2C_UNK func_00101D78();                            /* extern */
M2C_UNK func_001066D0();                            /* extern */
M2C_UNK func_0010AED8();                            /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
extern s32 D_003876B4;

void func_001056D8(void) {
    func_00101700(0);
    func_00101700(1);
    func_00101D78();
    func_0028BB60(D_003876B4);
    D_003876B4 = 0;
    func_001066D0();
    func_0010AED8();
}
