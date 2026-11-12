#include "m2c_macros.h"

void func_003B7A38(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
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
    d = ent + 0x7C;
    M2C_FIELD(ent, u16 *, 0) = M2C_FIELD(ent, u16 *, 0) | 8;
    M2C_FIELD(d, s32 *, 4) = 0;
    f1 = (f32)arg3;
    M2C_FIELD(d, f32 *, 8) = f1;
    if ((u8)arg2 != 0) {
        f0 = 1.0f / f1;
        M2C_FIELD(d, u16 *, 0) = M2C_FIELD(d, u16 *, 0) | 1;
    } else {
        f0 = -1.0f / f1;
        M2C_FIELD(d, u16 *, 0) = M2C_FIELD(d, u16 *, 0) | 2;
    }
    M2C_FIELD(d, f32 *, 0x10) = f0;
}
