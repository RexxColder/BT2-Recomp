#include "m2c_macros.h"

M2C_UNK func_0027A970(void *);                     /* extern */
extern void *D_003876A0;
extern void *D_00387AE8;

// Clears the flag at +0x54 of arg0 after func_0027A970 when the two status bits are set and D_00387AE8+0x54 == 1.
void func_0027AB98(void *arg0) {
    if ((M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 3) && (M2C_FIELD(D_00387AE8, u8 *, 0x54) == 1)) {
        func_0027A970(arg0);
        M2C_FIELD(arg0, s8 *, 0x54) = 0;
    }
}
