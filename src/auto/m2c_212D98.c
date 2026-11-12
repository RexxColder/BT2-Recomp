#include "m2c_macros.h"

extern void *D_00387930;

s32 func_00212D98(s32 arg0) {
    return M2C_FIELD(D_00387930, s32 *, 0x18) + (arg0 * 8);
}
