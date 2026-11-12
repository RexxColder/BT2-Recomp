#include "m2c_macros.h"

void func_003BC6A0(u8 *arg0);
M2C_UNK func_003BC7E8();                 /* extern */
M2C_UNK func_003BCB28();                      /* extern */
M2C_UNK func_003BCD00();                 /* extern */

void func_003BC798(s32 arg0, s32 arg1) {
    s32 sp[8];
    if (arg1 != 0) {
        func_003BC6A0((u8 *)arg0);
    }
    func_003BC7E8(sp, arg0);
    func_003BCB28(sp);
    func_003BCD00(arg0, sp);
}
