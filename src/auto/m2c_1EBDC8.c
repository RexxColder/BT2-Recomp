#include "m2c_macros.h"

s32 func_00126560();                                /* extern */
s32 func_001EBFF0();                                /* extern */
M2C_UNK func_001EC0D8();                            /* extern */
void *func_0028BAA8(s32);                           /* extern */
M2C_UNK memset(void *, M2C_UNK, s32);               /* extern */
extern void *D_0038790C;
extern s32 D_00387910;

void func_001EBDC8(s32 arg0) {
    s32 temp_v0_2;
    void *temp_v0;

    D_00387910 = arg0;
    temp_v0 = func_0028BAA8(0x6C);
    D_0038790C = temp_v0;
    memset(temp_v0, 0, 0x6C);
    if (func_00126560() == 0) {
        M2C_FIELD(D_0038790C, s32 *, 0x68) = 0xE;
    }
    temp_v0_2 = func_001EBFF0();
    if (temp_v0_2 == 0) {
        return;
    }
    M2C_FIELD(D_0038790C, void **, 0x60) = func_0028BAA8(temp_v0_2);
    memset(M2C_FIELD(D_0038790C, void **, 0x60), 0, temp_v0_2);
    func_001EC0D8();
}
