#include "m2c_macros.h"

M2C_UNK func_00312680(f32, s32, s32);               /* extern */
extern f32 D_00386EEC;

void BtlAnim_ApplyBlend(void *arg0) {
    s32 temp_a0;

    temp_a0 = arg0 + 0x1500;
    if (M2C_FIELD(arg0, u8 *, 0x1514) != 0) {
        M2C_FIELD(arg0, u8 *, 0x1514) = 0U;
        return;
    }
    func_00312680(D_00386EEC, temp_a0, temp_a0);
}
