#include "m2c_macros.h"

M2C_UNK StgSlot_Call02(M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_002E12E0();                            /* extern */
extern M2C_UNK D_00399E08 __attribute__((section(".data")));

void func_002E0790(void) {
    func_002E12E0();
    StgSlot_Call02(8, &D_00399E08, 0x3840);
}
