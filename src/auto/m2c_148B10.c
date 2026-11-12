#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void EftShotNull_Init(void *arg0, s32 arg1) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    memset(temp_s0, 0, 8);
    M2C_FIELD(temp_s0, s32 *, 4) = arg1;
}
