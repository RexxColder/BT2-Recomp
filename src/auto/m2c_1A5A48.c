#include "m2c_macros.h"

M2C_UNK func_001E7070(void *);                      /* extern */

void func_001A5A48(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x1C) != 0) && (M2C_FIELD(arg0, s32 *, 0x20) != 0)) {
        func_001E7070(arg0 + 0x18);
    }
}
