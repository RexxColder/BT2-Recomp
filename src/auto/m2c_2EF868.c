#include "m2c_macros.h"

extern M2C_UNK D_0039D6D0 __attribute__((section(".data")));

void func_002EF868(void) {
    if (M2C_FIELD(&D_0039D6D0, M2C_UNK (**)(s32), 0) != NULL) {
        M2C_FIELD(&D_0039D6D0, M2C_UNK (**)(s32), 0)(M2C_FIELD(&D_0039D6D0, s32 *, 4));
    }
}
