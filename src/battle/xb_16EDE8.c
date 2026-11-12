#include "m2c_macros.h"

s32 BtlScene_IsCharStopped(s32);                    /* extern */
M2C_UNK func_00129C38(void *, void *);              /* extern */

// Per-object flag update, same code as func_0015B568 with other field offsets (stop id at obj->0x38 + offset, guess).
void func_0016EDE8(void *arg0) {
    void *temp_s0;
    s32 temp_v0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (BtlScene_IsCharStopped(*M2C_FIELD(temp_s0, s32 **, 0xb0)) == 0) {
        M2C_FIELD(temp_s0, s32 *, 0) = (s32) (M2C_FIELD(temp_s0, s32 *, 0) & ~0x10);
        if (M2C_FIELD(arg0, u16 *, 8) & 1 & 0xFFFF) {
            func_00129C38(temp_s0 + 0x80, arg0 + 0x10);
            temp_v0 = M2C_FIELD(temp_s0, s32 *, 0);
            temp_v0 |= 0x10;
            M2C_FIELD(temp_s0, s32 *, 0) = temp_v0;
        }
        if (M2C_FIELD(arg0, u16 *, 8) & 4) {
            temp_v0 = M2C_FIELD(temp_s0, s32 *, 0) | 1;
            M2C_FIELD(temp_s0, s32 *, 0) = temp_v0;
        }
    }
}
