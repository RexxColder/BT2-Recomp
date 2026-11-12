#include "m2c_macros.h"

void *func_28BAA8(s32);
void *memset(void *, s32, u32);
u8 *func_002B24C8(u8 *arg0, u8 *arg1, s32 *arg2);
void Res_RelocateOffsets(void *, s32, s32);
extern void *D_00421C04 __attribute__((section(".data")));
extern void *D_00421388 __attribute__((section(".data")));

void func_003BBEF8(s32 arg0, void *arg1) {
    u8 *r;
    u8 *b;
    s32 outv;

    r = (u8 *)func_28BAA8(0x18);
    D_00421C04 = r;
    memset(r, 0, 0x18);
    b = (u8 *)D_00421388;
    M2C_FIELD(r, u8 **, 0) = b + (s32)(((u32)M2C_FIELD(b, s32 *, 4 * arg0) >> 2) << 2);
    M2C_FIELD(r, u8 **, 4) = func_002B24C8(M2C_FIELD(r, u8 **, 0), NULL, NULL);
    outv = M2C_FIELD(r, s32 *, 4);
    Res_RelocateOffsets(&outv, outv, outv);
    M2C_FIELD(r, s32 *, 8) = outv;
    M2C_FIELD(r, void **, 0x10) = arg1;
}
