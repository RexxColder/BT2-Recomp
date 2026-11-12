#include "m2c_macros.h"

s32 func_00100ED0(s32, s32, s32);                   /* extern */
extern u8 D_003876A8;
extern s32 D_003B0F70 __attribute__((section(".data")));

// Stores func_00100ED0(arg0, 0, flag) (flag = D_003876A8 != 0) into D_003B0F70, then clears the flag D_003876A8.
void func_002A3D38(s32 arg0) {
    D_003B0F70 = func_00100ED0(arg0, 0, D_003876A8 != 0);
    if (D_003876A8 != 0) {
        D_003876A8 = 0;
    }
}
