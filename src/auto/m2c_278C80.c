#include "m2c_macros.h"

M2C_UNK Ot_ResetEntries(s32, M2C_UNK);              /* extern */
M2C_UNK func_00278D98();                            /* extern */
M2C_UNK func_002791C8(void *, s32);                 /* extern */
M2C_UNK func_00279220();                            /* extern */
s32 func_002793C8(s32);                             /* extern */
void *func_0028BAA8(s32);                           /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *gOt;
extern s32 gOtFirst;

void func_00278C80(void) {
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_0028BAA8(0x38);
    gOt = temp_v0;
    memset(temp_v0, 0, 0x38);
    M2C_FIELD(gOt, s32 *, 0x30) = func_002793C8(0x68FFF);
    M2C_FIELD(gOt, s32 *, 0x30) = (s32) (M2C_FIELD(gOt, s32 *, 0x30) + 0xA000);
    temp_v0_2 = func_0028BAA8(func_002793C8(M2C_FIELD(gOt, s32 *, 0x30) + 0x10020));
    memset(temp_v0_2, 0, 4);
    func_002791C8(temp_v0_2, M2C_FIELD(gOt, s32 *, 0x30));
    func_00279220();
    func_00278D98();
    Ot_ResetEntries(gOtFirst, 0x2004);
}
