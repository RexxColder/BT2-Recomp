#include "m2c_macros.h"

s32 func_00266938(void *arg0) {
    return (*M2C_FIELD(arg0, s32 **, 0x44) & 0xC00000) != 0;
}
