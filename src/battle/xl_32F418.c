#include "m2c_macros.h"

// Clears a 64-bit word at +0x48 and sets the word at +4 to 0x2000 of the object given as the second argument.
s32 func_0032F418(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s64 *, 0x48) = 0;
    M2C_FIELD(arg1, s32 *, 4) = 0x2000;
    return 0;
}
