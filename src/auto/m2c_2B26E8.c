#include "m2c_macros.h"

s32 func_002CCA10(s32);                             /* extern */
M2C_UNK sceMpegSetBuffType(s32, s32);               /* extern */

void func_002B26E8(void *arg0, s32 arg1) {
    sceMpegSetBuffType(func_002CCA10(M2C_FIELD(arg0, s32 *, 0x3C)), arg1 == 0);
}
