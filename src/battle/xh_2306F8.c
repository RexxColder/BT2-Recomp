#include "m2c_macros.h"
M2C_UNK BattleSide_SetChara(void *, s32);        /* extern */

M2C_UNK func_00211418(void *, M2C_UNK);             /* extern */
s32 func_00217490(void *);                          /* extern */

// Sets side char 0x18B (if field 0x1534 nonzero) else 0x18A, clears field 0xA3C, calls func_00211418 0x200000, sets bit 1 at 0x8DC if func_00217490 result in [0xB8,0xC1).
void func_002306F8(void *arg0) {
    s32 temp_v0;

    s32 temp_a1 = 0x18B;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        temp_a1 = 0x18A;
    }
    BattleSide_SetChara(arg0, temp_a1);
    M2C_FIELD(arg0, s32 *, 0xA3C) = 0;
    func_00211418(arg0, 0x200000);
    temp_v0 = func_00217490(arg0);
    if (temp_v0 < 0xC1) {
        if (temp_v0 >= 0xB8) {
            M2C_FIELD(arg0, s32 *, 0x8DC) = (s32) (M2C_FIELD(arg0, s32 *, 0x8DC) | 1);
        }
    }
}
