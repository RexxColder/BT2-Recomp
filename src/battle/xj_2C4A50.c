#include "m2c_macros.h"

M2C_UNK func_002C4AA8();                         /* extern */
M2C_UNK func_002C4CC0();                         /* extern */
M2C_UNK func_002C4DB8();           /* extern */
M2C_UNK func_002C4E68();                         /* extern */
M2C_UNK func_002C4F00();                         /* extern */
M2C_UNK func_002C4FB0();                         /* extern */

void func_002C4A50(s32 arg0) {
    s32 sp[2];

    func_002C4DB8(arg0, &sp[0], &sp[1]);
    func_002C4AA8(arg0);
    func_002C4E68(arg0);
    func_002C4CC0(arg0);
    func_002C4F00(arg0);
    func_002C4FB0(arg0);
}
