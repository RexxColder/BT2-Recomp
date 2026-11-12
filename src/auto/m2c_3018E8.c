#include "m2c_macros.h"

M2C_UNK func_002EF098();                            /* extern */
M2C_UNK func_002EF0B0();                            /* extern */
M2C_UNK func_002F44A0();                            /* extern */
M2C_UNK func_0030C058(M2C_UNK);                     /* extern */
M2C_UNK func_0030C1E8(s32);                         /* extern */

void func_003018E8(void *arg0) {
    s32 temp_s0;
    void *temp_s1;

    temp_s1 = M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 4);
    temp_s0 = M2C_FIELD(temp_s1, s32 *, 0xE8);
    if (temp_s0 == 0) {
        return;
    }
    func_002F44A0(arg0);
    func_002EF098();
    func_0030C1E8(temp_s0);
    M2C_FIELD(temp_s1, s32 *, 0xE8) = 0;
    func_0030C058(0);
    func_002EF0B0();
}
