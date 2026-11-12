#include "m2c_macros.h"

M2C_UNK BtlAnim_SetBlend(f32, s32);                 /* extern */
s32 func_00211310(s32, M2C_UNK, M2C_UNK);                /* extern */
s32 func_00212320(s32);                             /* extern */
M2C_UNK func_0023AAA0(s32);                         /* extern */
s32 func_0023C710(s32);                             /* extern */
s32 func_00241F80(s32, s32);                        /* extern */
extern f32 D_00386C00;

s32 func_0023B5C0(s32 arg0) {
    if (func_00211310(arg0, 2, 1) != 0) {
        if (func_00241F80(arg0, func_00212320(arg0)) & 0x80) {
            func_0023AAA0(arg0);
        }
        BtlAnim_SetBlend(D_00386C00, arg0);
        return func_0023C710(arg0);
    }
    return -1;
}
