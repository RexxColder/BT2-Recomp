#include "m2c_macros.h"

// Moves a sprite-like record (u16 fields at +4/+8 by arg1, +6/+10 by arg2) when its flag word at +0 has bit 0 set.
void func_00113B00(void *arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(arg0, s32 *, 0) & 1) {
        M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) + arg1);
        M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) + arg1);
        M2C_FIELD(arg0, u16 *, 6) = (u16) (M2C_FIELD(arg0, u16 *, 6) + arg2);
        M2C_FIELD(arg0, u16 *, 0xA) = (u16) (M2C_FIELD(arg0, u16 *, 0xA) + arg2);
    }
}
