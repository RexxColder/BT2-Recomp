#include "m2c_macros.h"

extern M2C_UNK D_003A0388 __attribute__((section(".data")));

void StgFx_Reset(void) {
    if (M2C_FIELD(&D_003A0388, M2C_UNK (**)(s32), 0) != NULL) {
        M2C_FIELD(&D_003A0388, M2C_UNK (**)(s32), 0)(M2C_FIELD(&D_003A0388, s32 *, 4));
    }
}
