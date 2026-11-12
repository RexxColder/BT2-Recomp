#include "m2c_macros.h"

void Rand_Seed(u32);                             /* extern */

void func_0028C718(s64 arg0) {
    Rand_Seed((u64) (arg0 << 0x20) >> 0x20);
}
