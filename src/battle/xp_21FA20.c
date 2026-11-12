#include "m2c_macros.h"

M2C_UNK BtlAnim_SetNoBlend(s32);                    /* extern */
M2C_UNK func_00206958(s32, s32);                     /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

s32 func_0021FA20(s32 arg0) {
    func_00206958(arg0, 0x20);
    BtlAnim_SetNoBlend(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 1, 0x20000, 1);
    func_002113C0(arg0, 0xE, 0x40, 1);
    func_002113C0(arg0, 9, 0x20, 1);
    return 6;
}
