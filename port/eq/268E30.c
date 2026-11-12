#include "common.h"

f32 ObjShadow_CalcScreenDist(f32 farg0, f32 farg1, s32 arg0, s32 arg1);
void func_00312490(void *arg0, void *arg1, void *arg2);
void func_00312650(void *arg0, s32 arg1, s32 arg2);
void func_00312A50(void *arg0, s32 arg1, void *arg2, void *arg3);
void *memset(void *dst, s32 val, u32 n);
void sceVu0MulMatrix(void *arg0, void *arg1, void *arg2);
void sceVu0Normalize(void *arg0, void *arg1);
void sceVu0ViewScreenMatrix(void *arg0, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern s32 D_00387A44;

void func_00268E30(s32 arg0, u8 *arg1) {
    s32 sp10[4] __attribute__((aligned(16)));
    s32 sp20[4] __attribute__((aligned(16)));
    s32 sp30[16] __attribute__((aligned(16)));
    s32 sp70[16] __attribute__((aligned(16)));
    s32 spB0[4] __attribute__((aligned(16)));
    f32 dist;
    s32 s2;

    s2 = (s32)(arg1 + 0x20);
    memset(spB0, 0, 0x10);
    *(f32 *)((u8 *)spB0 + 0x8) = 1.0f;
    func_00312650(sp20, D_00387A44 + 0xE540, s2);
    sceVu0Normalize(sp20, sp20);
    func_00312490(sp10, sp20, spB0);
    sceVu0Normalize(sp10, sp10);
    dist = ObjShadow_CalcScreenDist(*(f32 *)(arg1 + 0x8), 254.0f, D_00387A44 + 0xE540, s2);
    sceVu0ViewScreenMatrix(sp30, dist, 1.0f, 1.0f, 2048.0f, 2048.0f, 1.0f, 16777216.0f, 1.0f, 16777216.0f);
    func_00312A50(sp70, s2, sp20, sp10);
    sceVu0MulMatrix(arg1 + 0x80, sp30, sp70);
}
