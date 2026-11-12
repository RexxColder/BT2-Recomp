#include "m2c_macros.h"

M2C_UNK func_001DFCA0(void *, s32, s32);                    /* extern */

// Forwards field 0x21C0 and arg1&0xFF to func_001DFCA0 with arg0.
void func_001DFD28(void *arg0, s32 arg1) {
    func_001DFCA0(arg0, M2C_FIELD(arg0, s32 *, 0x21C0), arg1 & 0xFF);
}
