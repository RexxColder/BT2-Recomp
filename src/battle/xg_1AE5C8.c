#include "m2c_macros.h"

/* Clears two flag bytes in the sub-object at +0x38 and sets byte +1 of arg0 to 3, when arg0 is non-null. */
void func_001AE5C8(void *arg0) {
    void *temp_v0;

    if (arg0 != NULL) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_v0, s8 *, 0x5D) = 0;
        M2C_FIELD(temp_v0, s8 *, 0x162) = 0;
        M2C_FIELD(arg0, s8 *, 1) = 3;
    }
}
