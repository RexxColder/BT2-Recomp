#include "m2c_macros.h"

M2C_UNK func_002E0108();                            /* extern */
M2C_UNK func_002E1A60(s32, M2C_UNK *, M2C_UNK);     /* extern */
extern s32 D_00347624 __attribute__((section(".data")));
extern M2C_UNK D_00347630 __attribute__((section(".data")));

void func_002E00B8(s32 arg0) {
    func_002E0108();
    if (arg0 != 0) {
        func_002E1A60(arg0, &D_00347630, 0x100);
        D_00347624 = arg0 + 0x180;
    }
}
