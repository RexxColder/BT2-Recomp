#include "m2c_macros.h"

void func_001DFE00(void *, s32, s32, f32);                    /* extern */

// Forwards field 0x21C0 and arg1&0xFF to func_001DFE00 with arg0 (f12 passes through).
void func_001DFE98(void *arg0, s32 arg1, f32 farg0) {
    func_001DFE00(arg0, M2C_FIELD(arg0, s32 *, 0x21C0), arg1 & 0xFF, farg0);
}
