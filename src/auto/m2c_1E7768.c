#include "m2c_macros.h"

M2C_UNK func_001E7F30(void *);                      /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern s32 D_003878F4;

void func_001E7768(void *arg0, s32 *arg1) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    memset(temp_s0, 0, 0xA0);
    M2C_FIELD(temp_s0, s32 *, 0x68) = (s32) *arg1;
    M2C_FIELD(temp_s0, s32 *, 0) = (s32) (D_003878F4 + 8);
    func_001E7F30(arg0);
}
