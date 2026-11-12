#include "m2c_macros.h"

void *memset(void *, s32, u32);
s32 func_2B30E0(void *, s32, s32, s32, s32);
s32 func_28BAA8(s32);
s32 func_2B4038(void *);
s32 func_2B4E18(s32, s32);
void func_2B7290(s32, s32);

void func_003B4A70(void *arg0) {
    u8 *p;
    s32 r1;
    s32 r2;
    s32 r3;

    p = (u8 *)arg0 + 0x90;
    memset(p, 0, 0x30);
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
    M2C_FIELD(p, s32 *, 0) = 1;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0x1E0;
    M2C_FIELD(arg0, s32 *, 0xA0) = 3;
    M2C_FIELD(arg0, s32 *, 0xA4) = 4;
    M2C_FIELD(arg0, s32 *, 0x98) = 0x280;
    M2C_FIELD(arg0, s32 *, 0x94) = 0x7A1200;
    M2C_FIELD(arg0, s32 *, 0xB4) = 0;
    r1 = func_2B30E0(p, 0x280, 0x1E0, 3, 4);
    M2C_FIELD(arg0, s32 *, 0xAC) = r1;
    r2 = func_28BAA8(r1);
    M2C_FIELD(arg0, s32 *, 0xA8) = r2;
    r3 = func_2B4038(p);
    M2C_FIELD(arg0, s32 *, 0xC0) = r3;
    func_2B4E18(r3, 0);
    func_2B7290(M2C_FIELD(arg0, s32 *, 0xC0), 1);
}
