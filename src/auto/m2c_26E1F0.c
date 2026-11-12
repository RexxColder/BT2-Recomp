#include "m2c_macros.h"

s32 func_0026CD98(u8 *, u8 *);                             /* extern */

void func_0026E1F0(void *arg0, u8 *arg1) { /* asm 0x26E1F0 passes a1 (the label) through to 26CD98 */
    s32 temp_v0;

    temp_v0 = func_0026CD98((u8 *)(unsigned long)(u32)M2C_FIELD(arg0, s32 *, 4), arg1);
    if (temp_v0 >= 0) {
        M2C_FIELD(arg0, s32 *, 8) = temp_v0;
        M2C_FIELD(arg0, u8 *, 0x11) = (u8) (M2C_FIELD(arg0, u8 *, 0x11) | 0x10);
    }
}
