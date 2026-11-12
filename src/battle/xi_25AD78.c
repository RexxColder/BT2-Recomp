#include "m2c_macros.h"

M2C_UNK func_003126C8();                    /* extern */
extern s32 D_00387A30;

// Two calls to func_003126C8: (arg0, &D_00387A30+0x2C0) then (arg1, &D_00387A30+0x2D0).
void func_0025AD78(s32 arg0, s32 arg1) {
    func_003126C8(arg0, D_00387A30 + 0x2C0);
    func_003126C8(arg1, D_00387A30 + 0x2D0);
}
