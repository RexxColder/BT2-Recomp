#include "m2c_macros.h"

s32 BtlScene_IsCharStopped(s32);                    /* extern */
M2C_UNK func_00129C38(void *, void *);              /* extern */
void func_0015D988(s32, void *, s32, s32);   /* extern */
void *func_001F3758();                              /* extern */

/* Per-actor update: when the char is not stopped, sets flag bits 0x20/0x1 from input bits in arg0+8. */
void func_0015E238(void *arg0) {
    s32 *temp_s2;
    s32 temp_s3;
    void *temp_s0;

    temp_s3 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    temp_s2 = M2C_FIELD(temp_s0, s32 **, 0xC0);
    if (BtlScene_IsCharStopped(*temp_s2) == 0) {
        if (M2C_FIELD(arg0, u16 *, 8) & 1 & 0xFFFF) {
            func_00129C38(temp_s0 + 0x90, arg0 + 0x10);
            if (!(M2C_FIELD(temp_s0, s32 *, 0) & 0x20)) {
                func_0015D988(*temp_s2, arg0, temp_s3, 1);
                M2C_FIELD(temp_s0, s32 *, 0) = (s32) (M2C_FIELD(temp_s0, s32 *, 0) | 0x20);
            }
        }
        if (M2C_FIELD(arg0, u16 *, 8) & 4) {
            M2C_FIELD(temp_s0, s32 *, 0) = (s32) (M2C_FIELD(temp_s0, s32 *, 0) | 1);
        }
    }
}
