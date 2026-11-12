#include "m2c_macros.h"

s32 func_002411A0();                                /* extern */

s32  func_00241C18(void *arg0) {
    return (s16)(M2C_FIELD(((func_002411A0(arg0) * 2) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x980)), s16 *, 0xB2));
}
