#include "m2c_macros.h"

M2C_UNK func_001E69A0(void *, void *);              /* extern */
M2C_UNK func_001E6DE8(void *, void *);              /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern s32 *D_003878E8;

void func_001E6E38(void *arg0, void *arg1) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    memset(temp_s0, 0, 0x2240);
    if (M2C_FIELD(arg1, s32 *, 0) != 0) {
        M2C_FIELD(temp_s0, void **, 0x40) = (void *) (temp_s0 + 0x50);
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
    } else if (M2C_FIELD(arg1, s32 *, 4) != 0) {
        M2C_FIELD(temp_s0, s32 *, 8) = 1;
        M2C_FIELD(temp_s0, void **, 0x44) = (void *) (temp_s0 + 0x50);
    }
    M2C_FIELD(temp_s0, s32 *, 0) = 1;
    func_001E6DE8(temp_s0, arg1);
    func_001E69A0(temp_s0, arg1);
    *D_003878E8 += 1;
}
