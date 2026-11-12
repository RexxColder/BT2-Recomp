#include "m2c_macros.h"

// Returns 0x20 if the word at +0xB74 of arg0 is not positive, else 0xAA.
s32 func_0023C780(void *arg0) {
    return (M2C_FIELD(arg0, s32 *, 0xB74) > 0) ? 0xAA : 0x20;
}
