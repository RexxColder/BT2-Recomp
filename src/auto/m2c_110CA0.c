#include "m2c_macros.h"

M2C_UNK func_0010CD18(s32, M2C_UNK);                /* extern */
M2C_UNK func_0010F220(s32, M2C_UNK);                /* extern */
M2C_UNK func_0010F2A8(s32, M2C_UNK);                /* extern */
M2C_UNK func_0010F3F0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0010F570(s32, M2C_UNK);                /* extern */
M2C_UNK func_00110108(s32, M2C_UNK);                /* extern */
s32 func_0020A5C0(M2C_UNK);                         /* extern */

void func_00110CA0(s32 arg0, M2C_UNK arg1) {
    if (func_0020A5C0(arg1) != 0) {
        func_0010CD18(arg0, arg1);
    }
    func_0010F3F0(arg0, arg1);
    func_0010F570(arg0, arg1);
    func_0010F2A8(arg0, arg1);
    func_0010F220(arg0, arg1);
    func_00110108(arg0, arg1);
}
