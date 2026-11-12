#include "m2c_macros.h"

extern M2C_UNK D_003A0380 __attribute__((section(".data")));

void StgModel_InitStage(void) {
    if (M2C_FIELD(&D_003A0380, M2C_UNK (**)(s32), 0) != NULL) {
        M2C_FIELD(&D_003A0380, M2C_UNK (**)(s32), 0)(M2C_FIELD(&D_003A0380, s32 *, 4));
    }
}
