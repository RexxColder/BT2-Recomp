#include "m2c_macros.h"

M2C_UNK EftStorm_MoveRain();                        /* extern */
M2C_UNK EftStorm_SpawnBolt(void *);                 /* extern */
M2C_UNK EftTexSet_Keep32(s32, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_00143798();                            /* extern */
extern void *D_003876A0;
extern s32 gEftStorm;

void func_00142738(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    void *var_s0;

    var_s0 = gEftStorm + 0x210;
    EftTexSet_Keep32(gEftStorm, 1, 0);
    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 0x100) {
        return;
    }
    var_s1 = 3;
    do {
        temp_v0 = M2C_FIELD(var_s0, s32 *, 0x20);
        if (temp_v0 != 0) {
            M2C_FIELD(var_s0, s32 *, 0x20) = (s32) (temp_v0 - 1);
        } else {
            temp_v0_2 = M2C_FIELD(var_s0, s32 *, 0x10);
            if (temp_v0_2 != 0) {
                M2C_FIELD(var_s0, s32 *, 0x10) = (s32) (temp_v0_2 - 1);
            } else {
                EftStorm_SpawnBolt(var_s0);
            }
        }
        var_s1 -= 1;
        var_s0 += 0x30;
    } while (var_s1 >= 0);
    EftStorm_MoveRain();
    func_00143798();
}
