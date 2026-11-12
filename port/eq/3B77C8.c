#include "m2c_macros.h"

void func_003B77C8(void *arg0, s32 arg1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17) {
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
    d = ent + 0x94;
    M2C_FIELD(ent, u16 *, 0) = M2C_FIELD(ent, u16 *, 0) | 0x10;
    f0 = (f32)M2C_FIELD(p, s32 *, 4);
    M2C_FIELD(d, f32 *, 0) = f0;
    f1 = (f32)M2C_FIELD(p, s32 *, 8);
    M2C_FIELD(d, s32 *, 8) = 0;
    M2C_FIELD(d, f32 *, 0x24) = f15;
    M2C_FIELD(d, f32 *, 0x10) = f16;
    M2C_FIELD(d, f32 *, 0x14) = f17;
    M2C_FIELD(d, f32 *, 4) = f1;
    M2C_FIELD(d, f32 *, 0x18) = f12;
    M2C_FIELD(d, f32 *, 0x1C) = f13;
    M2C_FIELD(d, f32 *, 0x20) = f14;
    M2C_FIELD(d, s32 *, 0xC) = 0;
}
