#include "m2c_macros.h"

void func_0027EBA8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x500) == 0) {
        M2C_FIELD(arg0, s8 *, 0x503) = 0;
        M2C_FIELD(arg0, s32 *, 0x510) = 0;
        M2C_FIELD(arg0, s32 *, 0x504) = (s32) M2C_FIELD(arg0, s32 *, 0x520);
    }
}
