#include "m2c_macros.h"

M2C_UNK func_00297858();                     /* extern */
M2C_UNK func_002F6D90();                     /* extern */

void func_002979F0(s32 arg0) {
    if (arg0 != 0) {
        func_00297858(1);
        func_002F6D90(0);
        return;
    }
    func_00297858(0);
    func_002F6D90(1);
}
