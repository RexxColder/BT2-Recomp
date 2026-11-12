#include "m2c_macros.h"

M2C_UNK func_002EBB08(s32);                         /* extern */
M2C_UNK func_002EC160(s32);                         /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00387688;
extern s32 D_0038768C;
extern s32 D_00387690;
extern s32 D_00387698;
extern s32 D_0038769C;
extern M2C_UNK D_00387F80 __attribute__((section(".data")));

void func_00100E78(void) {
    if (D_0038768C != 0) {
        func_002EC160(D_0038768C);
        func_002EBB08(D_0038768C);
    }
    memset(&D_00387F80, 0, 0x618);
    D_00387688 = 0;
    D_0038768C = 0;
    D_00387690 = 0;
    D_00387698 = 0;
    D_0038769C = 0;
}
