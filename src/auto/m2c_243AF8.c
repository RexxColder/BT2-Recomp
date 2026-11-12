#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK gColorFade __attribute__((section(".data")));

void func_00243AF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    memset(&gColorFade, 0, 0x18);
    M2C_FIELD(&gColorFade, s32 *, 0) = 2;
    M2C_FIELD(&gColorFade, s32 *, 4) = arg0;
    M2C_FIELD(&gColorFade, s32 *, 8) = arg1;
    M2C_FIELD(&gColorFade, s32 *, 0xC) = arg2;
    M2C_FIELD(&gColorFade, s32 *, 0x10) = 0;
    M2C_FIELD(&gColorFade, s32 *, 0x14) = (s32) (0x80 / arg3);
}
