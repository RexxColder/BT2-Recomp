#include "m2c_macros.h"

void *func_0028BAA8(M2C_UNK);                       /* extern */
M2C_UNK func_002A85B0(s32, s32, s32, s32);          /* extern */
M2C_UNK func_002A8858(void *, M2C_UNK);             /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_00387E04;

void func_002A85D0(void) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_0028BAA8(0xB4);
    D_00387E04 = temp_v0;
    memset(temp_v0, 0, 0xB4);
    func_002A8858(D_00387E04 + 0xA0, 4);
    var_a2 = 0;
    var_a3 = 0;
    do {
        temp_v1 = var_a2 * 8;
        var_a2 += 1;
        temp_a0 = M2C_FIELD(D_00387E04, s32 *, 0xA4);
        temp_v0_2 = D_00387E04 + var_a3;
        temp_a1 = var_a2 < 4;
        var_a3 += 0x28;
        M2C_FIELD((temp_v1 + temp_a0), void **, 4) = temp_v0_2;
    } while (temp_a1 != 0);
    func_002A85B0(temp_a0, temp_a1, var_a2, var_a3);
}
