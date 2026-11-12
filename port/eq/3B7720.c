#include "m2c_macros.h"

void func_003B7720(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 f12) {
    u8 *ent;
    u8 *p;
    u8 *d;

    ent = (u8 *)M2C_FIELD(arg0, u8 **, 0) + (arg1 * 0xBC);
    p = (u8 *)M2C_FIELD(ent, u8 **, 4);
    if (M2C_FIELD(p, s32 *, 0) & 2) {
        return;
    }
    d = ent + 8;
    M2C_FIELD(ent, u16 *, 0) = M2C_FIELD(ent, u16 *, 0) | 1;
    if (f12 == 0.0f) {
        M2C_FIELD(d, u16 *, 0) = M2C_FIELD(d, u16 *, 0) | 1;
    } else {
        M2C_FIELD(d, u16 *, 0) = M2C_FIELD(d, u16 *, 0) | 3;
    }
    M2C_FIELD(d, f32 *, 4) = 0.0f;
    M2C_FIELD(d, f32 *, 0xC) = f12;
    M2C_FIELD(d, f32 *, 8) = (f32)arg4;
    M2C_FIELD(d, f32 *, 0x10) = (f32)M2C_FIELD(p, s32 *, 4);
    M2C_FIELD(d, f32 *, 0x14) = (f32)M2C_FIELD(p, s32 *, 8);
    M2C_FIELD(d, s32 *, 0x18) = M2C_FIELD(p, s32 *, 4);
    M2C_FIELD(d, s32 *, 0x24) = arg3;
    M2C_FIELD(d, s32 *, 0x1C) = M2C_FIELD(p, s32 *, 8);
    M2C_FIELD(d, s32 *, 0x20) = arg2;
}
