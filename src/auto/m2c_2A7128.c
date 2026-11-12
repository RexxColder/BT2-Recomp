#include "m2c_macros.h"

f32 Gsc_GetFloatOr(f32);                            /* extern */
s32 Gsc_GetIntOr(s32);                              /* extern */
M2C_UNK func_002A0010(M2C_UNK);                     /* extern */
void *func_002A40F8();                              /* extern */
void *func_002A4108();                              /* extern */

s32 func_002A7128(s32 arg0) {
    void *temp_s0;
    void *temp_s1;

    if (arg0 == 0) {
        temp_s0 = func_002A40F8();
        temp_s1 = func_002A4108();
        func_002A0010(0x64);
        M2C_FIELD(temp_s1, s32 *, 0x40) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x40));
        M2C_FIELD(temp_s1, s32 *, 0x44) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x44));
        M2C_FIELD(temp_s1, s32 *, 0x48) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x48));
        M2C_FIELD(temp_s1, s32 *, 0x4C) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x4C));
        M2C_FIELD(temp_s1, s32 *, 0x50) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x50));
        M2C_FIELD(temp_s1, s32 *, 0x54) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x54));
        func_002A0010(0x61);
        M2C_FIELD(temp_s1, f32 *, 0) = Gsc_GetFloatOr(M2C_FIELD(temp_s0, f32 *, 0));
        M2C_FIELD(temp_s1, f32 *, 4) = Gsc_GetFloatOr(M2C_FIELD(temp_s0, f32 *, 4));
        func_002A0010(0x73);
        M2C_FIELD(temp_s1, f32 *, 8) = Gsc_GetFloatOr(M2C_FIELD(temp_s0, f32 *, 8));
        func_002A0010(0x63);
        M2C_FIELD(temp_s1, s8 *, 0xC) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0xC));
        M2C_FIELD(temp_s1, s8 *, 0xD) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0xD));
        M2C_FIELD(temp_s1, s8 *, 0xE) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0xE));
        M2C_FIELD(temp_s1, s8 *, 0xF) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0xF));
        func_002A0010(0x70);
        M2C_FIELD(temp_s1, s32 *, 0x10) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x10));
        M2C_FIELD(temp_s1, s32 *, 0x14) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x14));
        func_002A0010(0x77);
        M2C_FIELD(temp_s1, s32 *, 0x18) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x18));
        func_002A0010(0x54);
        M2C_FIELD(temp_s1, s32 *, 0x20) = Gsc_GetIntOr(M2C_FIELD(temp_s0, s32 *, 0x20));
        func_002A0010(0x4F);
        M2C_FIELD(temp_s1, s16 *, 0x28) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u16 *, 0x28));
        M2C_FIELD(temp_s1, s16 *, 0x2A) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u16 *, 0x2A));
        func_002A0010(0x43);
        M2C_FIELD(temp_s1, s8 *, 0x24) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0x24));
        M2C_FIELD(temp_s1, s8 *, 0x25) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0x25));
        M2C_FIELD(temp_s1, s8 *, 0x26) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0x26));
        M2C_FIELD(temp_s1, s8 *, 0x27) = Gsc_GetIntOr((s32) M2C_FIELD(temp_s0, u8 *, 0x27));
    }
    return 1;
}
