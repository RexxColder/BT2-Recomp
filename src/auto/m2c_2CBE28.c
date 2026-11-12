#include "m2c_macros.h"

M2C_UNK func_002DA638(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK sceMpegInit();                              /* extern */
extern s32 D_00346E5C __attribute__((section(".data")));
extern M2C_UNK D_00399CE8 __attribute__((section(".data")));

void func_002CBE28(void) {
    if (D_00346E5C != 0) {
        sceMpegInit();
        func_002DA638(&D_00399CE8, 0, 0x48);
    }
}
