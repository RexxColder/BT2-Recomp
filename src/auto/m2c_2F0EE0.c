#include "m2c_macros.h"

s32 func_002E7E68(void *);                          /* extern */
M2C_UNK func_002E8558(void *);                      /* extern */
M2C_UNK func_002F08D8(void *);                      /* extern */
M2C_UNK func_002F0C68(void *);                      /* extern */
M2C_UNK func_002F0E50(void *);                      /* extern */

void func_002F0EE0(void *arg0) {
    s16 temp_a0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 4);
    if (func_002E7E68(temp_s0) == 0) {
        func_002F08D8(arg0);
    }
    func_002E8558(temp_s0);
    if (func_002E7E68(temp_s0) == 3) {
        func_002F0C68(arg0);
    }
    temp_a0 = M2C_FIELD(temp_s0, s16 *, 0x98);
    if ((temp_a0 == 0xA) || (temp_a0 == 0x14) || (temp_a0 == 0xB) || (temp_a0 == 0xC) || (temp_a0 == 0xF)) {
        func_002F0E50(arg0);
    }
}
