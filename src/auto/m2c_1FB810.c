#include "m2c_macros.h"

M2C_UNK atanf(f32);                                 /* extern */

void func_001FB810(void *arg0) {
    atanf(M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), f32 *, 0xFB8));
}
