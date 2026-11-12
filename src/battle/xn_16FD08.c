#include "m2c_macros.h"

s32 BtlScene_IsCharStopped(s32);                    /* extern */
M2C_UNK func_00129C38(void *, void *);              /* extern */
void func_0016F118(s32, void *, s32, s32);   /* extern */
void *func_001F3758();                              /* extern */

/* Per-actor update: sets flag bits from input bits in arg0+8 (see neighbours). */
void func_0016FD08(void *arg0) {
    s32 *temp_s2;
    s32 temp_s3;
    s32 temp_v0;
    void *temp_s1;

    temp_s3 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    temp_s2 = M2C_FIELD(temp_s1, s32 **, 0xB0);
    if (BtlScene_IsCharStopped(*temp_s2) != 0) {
        return;
    }
    if (M2C_FIELD(arg0, u16 *, 8) & 1 & 0xFFFF) {
        func_00129C38(temp_s1 + 0x80, arg0 + 0x10);
        func_0016F118(*temp_s2, arg0, temp_s3, 1);
        temp_v0 = M2C_FIELD(temp_s1, s32 *, 0);
        if (!(temp_v0 & 0x20)) {
            M2C_FIELD(temp_s1, s32 *, 0) = (s32) (temp_v0 | 0x20);
        }
    }
    if (M2C_FIELD(arg0, u16 *, 8) & 4) {
        M2C_FIELD(temp_s1, s32 *, 0) = (s32) (M2C_FIELD(temp_s1, s32 *, 0) | 1);
    }
}
