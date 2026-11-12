#include "m2c_macros.h"

M2C_UNK func_001EBC70(s32, s32, s32, M2C_UNK);      /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */

void func_001C2310(void *arg0) {
    s32 *var_v1;
    s32 *var_v1_2;
    s32 temp_s0;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;
    s32 var_v0_2;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    memset(temp_s0, 0, 0x20D50);
    func_001EBC70(temp_s0 + 0xF400, temp_s0, temp_s0 + 0xF000, 0x100);
    var_a0 = 0xFF;
    var_v1 = temp_s0 + 0xF3FC;
    var_v0 = temp_s0 + 0xEF10;
    do {
        var_a0 -= 1;
        *var_v1 = var_v0;
        var_v1 -= 1;
        var_v0 -= 0xF0;
    } while (var_a0 >= 0);
    func_001EBC70(temp_s0 + 0x20D48, temp_s0 + 0xF408, temp_s0 + 0x1F128, 0x708);
    var_a0_2 = 0x707;
    var_v1_2 = temp_s0 + 0x20D44;
    var_v0_2 = temp_s0 + 0x1F104;
    do {
        var_a0_2 -= 1;
        *var_v1_2 = var_v0_2;
        var_v1_2 -= 1;
        var_v0_2 -= 0x24;
    } while (var_a0_2 >= 0);
    func_001EBC70(temp_s0 + 0xF400, temp_s0, temp_s0 + 0xF000, 0x100);
    func_001EBC70(temp_s0 + 0x20D48, temp_s0 + 0xF408, temp_s0 + 0x1F128, 0x708);
}
