#include "m2c_macros.h"

void *func_28BAA8(s32);
void *memset(void *, s32, u32);
void func_2B6208(void *);
void func_003B4A70(void *);
extern void *D_00421384 __attribute__((section(".data")));
extern void *D_0038B950 __attribute__((section(".data")));

void func_003B43F0(void) {
    void *r1;
    void *r2;

    r1 = func_28BAA8(0x1F0);
    D_00421384 = r1;
    memset(r1, 0, 0x1F0);
    r2 = func_28BAA8(0x12D400);
    D_0038B950 = r2;
    memset(r2, 0, 0x12D400);
    memset(D_00421384, 0, 0x20);
    M2C_FIELD(D_00421384, f32 *, 0) = M2C_BITWISE(f32, (s32)0x426FC28F);
    M2C_FIELD(D_00421384, s32 *, 4) = 1;
    M2C_FIELD(D_00421384, s32 *, 8) = 1;
    M2C_FIELD(D_00421384, s32 *, 0xC) = 0;
    func_2B6208(D_00421384);
    func_003B4A70((u8 *)D_00421384 + 0x20);
}
