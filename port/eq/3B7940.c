#include "m2c_macros.h"

void func_003B7940(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *ent;
    u8 *p;
    u8 *d;
    f32 f0;
    f32 f1;

    ent = (u8 *)M2C_FIELD(arg0, u8 **, 0) + (arg1 * 0xBC);
    p = (u8 *)M2C_FIELD(ent, u8 **, 4);
    if (M2C_FIELD(p, s32 *, 0) & 2) {
        return;
    }
    d = ent + 0x64;
    f0 = (f32)arg2 / 255.0f;
    f1 = (f32)arg3 / 255.0f;
    M2C_FIELD(ent, u16 *, 0) = M2C_FIELD(ent, u16 *, 0) | 4;
    M2C_FIELD(d, s32 *, 4) = 0;
    M2C_FIELD(d, u16 *, 0) = M2C_FIELD(d, u16 *, 0) | 1;
    M2C_FIELD(d, f32 *, 8) = (f32)arg4;
    M2C_FIELD(d, f32 *, 0xC) = f0;
    M2C_FIELD(d, f32 *, 0x10) = f0;
    M2C_FIELD(d, f32 *, 0x14) = f1;
}
