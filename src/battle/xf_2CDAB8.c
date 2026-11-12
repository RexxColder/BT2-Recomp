#include "m2c_macros.h"

s32 func_002CDAB8(void *arg0) {
    void **temp_a0;
    void *temp_s0;
    s32 temp_v0;

    temp_s0 = arg0 + (M2C_FIELD(arg0, s32 *, 0x200C) * 0x74) + 0x1320;
    temp_a0 = M2C_FIELD(temp_s0, void ***, 4);
    temp_v0 = M2C_FIELD(*temp_a0, s32 (**)(void *, M2C_UNK), 0x24)(temp_a0, 1);
    if (temp_v0 < ((s32) (M2C_FIELD(temp_s0, s32 *, 0xC) * 0x50) / 100)) {
        return 0;
    }
    return 1;
}
