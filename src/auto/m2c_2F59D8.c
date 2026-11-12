#include "m2c_macros.h"

M2C_UNK func_002EA050(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037CB60 __attribute__((section(".data")));

s32 func_002F59D8(s32 arg0, s32 arg1) {
    u32 temp_v0;
    void **temp_v0_2;

    if ((arg0 == 0) || (arg1 < 0)) {
        func_002EA050(&D_0037CB60);
        return -1;
    }
    temp_v0_2 = M2C_FIELD(((arg1 * 4) + arg0), void ***, 0x18);
    if (temp_v0_2 != NULL) {
        temp_v0 = M2C_FIELD(*temp_v0_2, u32 (**)(void *, M2C_UNK), 0x24)(temp_v0_2, 1);
        return (s32) ((temp_v0 >> 0x1F) + temp_v0) >> 1;
    }
    return 0;
}
