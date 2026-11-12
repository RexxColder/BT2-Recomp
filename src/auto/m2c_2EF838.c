#include "m2c_macros.h"

extern M2C_UNK D_0039D6C8 __attribute__((section(".data")));

void StgNav_Rebind(void) {
    if (M2C_FIELD(&D_0039D6C8, M2C_UNK (**)(s32), 0) != NULL) {
        M2C_FIELD(&D_0039D6C8, M2C_UNK (**)(s32), 0)(M2C_FIELD(&D_0039D6C8, s32 *, 4));
    }
}
