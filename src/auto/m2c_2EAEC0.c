#include "m2c_macros.h"

M2C_UNK func_002EBB38(s32);                         /* extern */
extern s32 D_00348D5C __attribute__((section(".data")));
extern s32 D_00367404 __attribute__((section(".data")));
extern s32 D_00367408 __attribute__((section(".data")));

void func_002EAEC0(void) {
    func_002EBB38(D_00367408);
    D_00367408 = 0;
    D_00367404 = 0;
    D_00348D5C = 0;
}
