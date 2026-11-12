#include "m2c_macros.h"

s32 BtlScene_IsCharStopped(s32);
void func_00129C38(void *, void *);
void func_00154260(s32, void *, s32, s32);
void *func_001F3758();

// Per-frame update of a character state (flags at +0 of the object at arg0+0x38): returns early while BtlScene_IsCharStopped holds; on bit 1 of arg0 +8 it runs two helpers and sets flag 0x20; bit 4 sets flag 1.
void func_00154B58(void *arg0) {
    s32 *temp_s2;
    s32 temp_s3;
    void *temp_s1;

    temp_s3 = M2C_FIELD(func_001F3758(arg0), s32 *, 0x38);
    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    temp_s2 = M2C_FIELD(temp_s1, s32 **, 0xC0);
    if (BtlScene_IsCharStopped(*temp_s2) != 0) {
        return;
    }
    if (M2C_FIELD(arg0, u16 *, 8) & 1) {
        func_00129C38((u8 *) temp_s1 + 0x90, (u8 *) arg0 + 0x10);
        func_00154260(*temp_s2, arg0, temp_s3, 1);
        if (!(M2C_FIELD(temp_s1, s32 *, 0) & 0x20)) {
            M2C_FIELD(temp_s1, s32 *, 0) = (s32) (M2C_FIELD(temp_s1, s32 *, 0) | 0x20);
        }
    }
    if (M2C_FIELD(arg0, u16 *, 8) & 4) {
        M2C_FIELD(temp_s1, s32 *, 0) = (s32) (M2C_FIELD(temp_s1, s32 *, 0) | 1);
    }
}
