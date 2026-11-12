#include "m2c_macros.h"

M2C_UNK func_001EBD88(s32);                         /* extern */

void func_001C2470(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    func_001EBD88(temp_s0 + 0xF400);
    func_001EBD88(temp_s0 + 0x20D48);
}
