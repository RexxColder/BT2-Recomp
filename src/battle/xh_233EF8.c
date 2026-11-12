#include "m2c_macros.h"

M2C_UNK BtlAnim_SetBlend(f32, s32);                 /* extern */
s32 func_00211310(s32, M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00212890(M2C_UNK);                     /* extern */
s32 func_0023C710(s32);                             /* extern */
extern f32 D_0038693C;

// If func_00211310(arg0,2,1) is set: flag set 0x100 on arg0, SetBlend with D_0038693C, func_00212890(0x5A), returns func_0023C710(arg0); else -1.
s32 func_00233EF8(s32 arg0) {
    if (func_00211310(arg0, 2, 1) != 0) {
        func_002113C0(arg0, 5, 0x100, 1);
        BtlAnim_SetBlend(D_0038693C, arg0);
        func_00212890(0x5A);
        return func_0023C710(arg0);
    }
    return -1;
}
