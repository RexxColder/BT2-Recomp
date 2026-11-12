#include "m2c_macros.h"

M2C_UNK func_001DFD48(void *, s32, s32, s32);                    /* extern */

// Forwards arg1, field 0x21C0 and arg2&0xFF to func_001DFD48 with arg0.
void func_001DFDE0(void *arg0, s32 arg1, s32 arg2) {
    func_001DFD48(arg0, arg1, M2C_FIELD(arg0, s32 *, 0x21C0), arg2 & 0xFF);
}
