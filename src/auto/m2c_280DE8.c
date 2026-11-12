#include "m2c_macros.h"

M2C_UNK func_0027AAB0(s32);                         /* extern */
M2C_UNK func_0027B988();                            /* extern */
M2C_UNK func_0027F9E8();                            /* extern */
M2C_UNK func_00282610();                            /* extern */
M2C_UNK func_002838E0();                            /* extern */
M2C_UNK func_00284FF8();                            /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
extern s32 D_00387AFC;

void func_00280DE8(void) {
    func_0027AAB0(D_00387AFC + 0x3090);
    func_0028BB60(D_00387AFC);
    D_00387AFC = 0;
    func_00282610();
    func_002838E0();
    func_00284FF8();
    func_0027F9E8();
    func_0027B988();
}
