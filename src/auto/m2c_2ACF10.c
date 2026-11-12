#include "m2c_macros.h"

M2C_UNK func_00101740();                            /* extern */
s32 func_00101E58();                                /* extern */
s32 func_001066E8(M2C_UNK, M2C_UNK);                /* extern */
s32 func_0010AB78(M2C_UNK *);                       /* extern */
extern void *D_003876A0;
extern M2C_UNK D_00387E10;

s32 func_002ACF10(void) {
    if ((func_001066E8(0, 0) == 0) && (func_0010AB78(&D_00387E10) != 0)) {
        M2C_FIELD(D_003876A0, s64 *, 0x4D8) = (s64) (M2C_FIELD(D_003876A0, s64 *, 0x4D8) ^ 0x100);
        func_00101740();
    }
    return func_00101E58() != 0;
}
