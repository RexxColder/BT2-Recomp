#include "m2c_macros.h"

M2C_UNK func_00297680();                            /* extern */
M2C_UNK func_00336EC8(s32);                         /* extern */
extern void *D_00387ED0;

void func_00297EC8(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_00387ED0, s32 *, 0x60);
    if (temp_v0 != 0) {
        M2C_FIELD(D_00387ED0, s32 *, 0x60) = (s32) (temp_v0 - 1);
        func_00336EC8(M2C_FIELD(((M2C_FIELD(D_00387ED0, s32 *, 0x60) * 4) + D_00387ED0), s32 *, 0x20));
        M2C_FIELD(((M2C_FIELD(D_00387ED0, s32 *, 0x60) * 4) + D_00387ED0), s32 *, 0x20) = 0;
        func_00336EC8(M2C_FIELD(((M2C_FIELD(D_00387ED0, s32 *, 0x60) * 4) + D_00387ED0), s32 *, 0x40));
        M2C_FIELD(((M2C_FIELD(D_00387ED0, s32 *, 0x60) * 4) + D_00387ED0), s32 *, 0x40) = 0;
        func_00297680();
    }
}
