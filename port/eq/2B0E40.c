#include "common.h"

void func_003126C8(u8 *arg0, u8 *arg1);
void func_00312638(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00312650(u8 *arg0, u8 *arg1, u8 *arg2);
void sceVu0UnitMatrix(u8 *arg0);
void sceVu0RotMatrixX(f32 farg0, u8 *arg1, u8 *arg2);
void sceVu0RotMatrixY(f32 farg0, u8 *arg1, u8 *arg2);
void sceVu0RotMatrixZ(f32 farg0, u8 *arg1, u8 *arg2);
void sceVu0ApplyMatrix(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_0029DFD0(u8 *arg0);
void func_00260A50(u8 *arg0);
extern f32 D_00387564;
extern f32 D_00387568;

void func_002B0E40(u8 *arg0) {
    u8 sp[0x70];
    u8 *s0;

    func_003126C8(sp, *(u8 **)arg0 + 0x9A0);
    func_00312638(*(u8 **)arg0 + 0x9A0, arg0 + 0xD0, arg0 + 0xF0);
    func_003126C8(*(u8 **)arg0 + 0x9B0, arg0 + 0xE0);
    s0 = sp + 0x10;
    if (*(u16 *)(arg0 + 0x190) == 0) {
        sceVu0UnitMatrix(s0);
        sceVu0RotMatrixY(D_00387564, s0, s0);
        sceVu0RotMatrixY(*(f32 *)(*(u8 **)arg0 + 0x9B4), s0, s0);
        sceVu0RotMatrixX(*(f32 *)(*(u8 **)arg0 + 0x9B0), s0, s0);
        sceVu0RotMatrixZ(*(f32 *)(*(u8 **)arg0 + 0x9B8), s0, s0);
        sceVu0ApplyMatrix(sp + 0x50, s0, arg0 + 0x100);
        func_00312650(*(u8 **)arg0 + 0x9A0, *(u8 **)arg0 + 0x9A0, sp + 0x50);
    }
    func_00312650(sp + 0x60, *(u8 **)arg0 + 0x9A0, sp);
    if (func_0029DFD0(sp + 0x60) < D_00387568) {
        func_003126C8(*(u8 **)arg0 + 0x9A0, sp);
    }
    *(f32 *)(*(u8 **)arg0 + 0x9F4) = *(f32 *)(arg0 + 0x150);
    func_00260A50(*(u8 **)arg0);
}
