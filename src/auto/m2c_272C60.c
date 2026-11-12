#include "m2c_macros.h"

s32 func_00273970(u8, s32);                         /* extern */
extern u8 D_003876A8;
extern s32 D_00387AB8;

void func_00272C60(s32 arg0) {
    D_00387AB8 = arg0;
    if (func_00273970(D_003876A8, arg0) != 0) {
        D_003876A8 = 0;
    }
}
