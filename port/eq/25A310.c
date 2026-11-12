#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_0025B688(u8 *arg0, s64 *arg1, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7,
                   f32 f8, f32 f9);
void func_003126C8(void *arg0, void *arg1);
void sceVu0UnitMatrix(void *arg0, s32 arg1);
extern u8 D_002C3630[];
extern u8 D_00376490[];
extern f32 D_00386DA0;
extern f32 D_00386DA4;
extern f32 D_00386DA8;
extern f32 D_00386DAC;
extern u8 *D_00387A30;

void func_0025A310(void) {
    s64 sp10[2];

    sp10[1] = *(s64 *)(D_00376490 + 8);
    sp10[0] = *(s64 *)(D_00376490 + 0);
    memset(D_00387A30 + 0x250, 0, 0xD0);
    func_0025B688(D_00387A30, sp10, D_00386DA0, 1.0f, D_00386DA4, 2048.0f, 2048.0f, 1.0f, D_00386DA8,
                  D_00386DAC, 65536.0f, 1.0f);
    *(s32 *)(D_00387A30 + 0x200) = 0;
    *(s32 *)(D_00387A30 + 0x204) = 0x1FF;
    *(s32 *)(D_00387A30 + 0x208) = 0;
    *(s32 *)(D_00387A30 + 0x20C) = 0x1BF;
    sceVu0UnitMatrix(D_00387A30 + 0x250, 0x1BF);
    func_003126C8(D_00387A30 + 0x2C0, D_002C3630);
    func_003126C8(D_00387A30 + 0x2D0, D_002C3630);
}
