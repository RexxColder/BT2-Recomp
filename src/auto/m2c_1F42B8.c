#include "m2c_macros.h"

extern s32 D_00387920;

void func_001F42B8(s32 arg0, s32 arg1) {
    if (D_00387920 != 0) {
        M2C_FIELD(((arg0 * 4) + D_00387920), s32 *, 0x30) = arg1;
    }
}
