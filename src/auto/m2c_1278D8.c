#include "m2c_macros.h"

s32  EftHit_GetMaxHits(void *arg0) {
    void *temp_a0;

    if (M2C_FIELD(arg0, s32 *, 0x68) == 0) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x64);
        if (temp_a0 != NULL) {
            return (s8)(M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x20), s8 *, 0x36));
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return (s8)(0);
    }
    return (s8)(0);
}
