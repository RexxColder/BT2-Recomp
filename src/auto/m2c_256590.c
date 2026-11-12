#include "m2c_macros.h"

M2C_UNK func_00250D90();                            /* extern */
M2C_UNK func_0026E908(s32);                         /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
extern s32 D_003879E8;

void func_00256590(void) {
    func_00250D90();
    func_0026E908(D_003879E8 + 4);
    func_0028BB60(D_003879E8);
}
