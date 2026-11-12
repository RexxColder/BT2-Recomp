#include "m2c_macros.h"

extern void *D_00387A40;

s32 func_00261060(s32 arg0) {
    return M2C_FIELD(D_00387A40, s32 *, 8) + ((arg0 & 0xFFFF) * 0x1520);
}
