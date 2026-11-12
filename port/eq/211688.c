#include "common.h"

void func_003126C8(void *arg0, void *arg1);
void func_00312638(void *arg0, void *arg1, s32 arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
s32 BtlChar_GetPos(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void sceVu0UnitMatrix(void *arg0);
void sceVu0RotMatrixX(f32 farg0, void *arg0, void *arg1);
void sceVu0RotMatrixY(f32 farg0, void *arg0, void *arg1);
void sceVu0RotMatrixZ(f32 farg0, void *arg0, void *arg1);
void sceVu0ApplyMatrix(void *arg0, void *arg1, void *arg2);
f32 func_0029DFD0(void *arg0);
void func_00260A50(void *arg0);
extern f32 D_00385A2C;
extern f32 D_00385A30;

#define BASE(a) (*(u8 **)((u8 *)(a) + 0x1530))

void func_00211688(void *arg0, s32 arg1) {
    f32 sp[4];
    f32 sp10[16];
    f32 sp50[4];
    s32 temp_s0;
    s32 temp_v0;
    s32 cond;
    s32 x;
    s32 y;

    func_003126C8(sp, BASE(arg0) + 0x9A0);
    temp_s0 = BtlChar_GetPos(arg0);
    temp_v0 = BtlChar_GetPos(arg0);
    func_00312638(BASE(arg0) + 0x9A0, (void *)temp_s0, temp_v0 + 0x60);
    temp_v0 = BtlChar_GetPos(arg0);
    func_003126C8(BASE(arg0) + 0x9B0, (void *)(temp_v0 + 0x10));

    x = func_00211310(arg0, 2, 2);
    y = func_00211310(arg0, 2, 0x400);
    cond = (!(arg1 & 0xFF)) ? 1 : ((y != 0) ? 1 : (x == 0));

    if (cond != 0) {
        sceVu0UnitMatrix(sp10);
        sceVu0RotMatrixY(D_00385A2C, sp10, sp10);
        sceVu0RotMatrixY(*(f32 *)(BASE(arg0) + 0x9B4), sp10, sp10);
        sceVu0RotMatrixX(*(f32 *)(BASE(arg0) + 0x9B0), sp10, sp10);
        sceVu0RotMatrixZ(*(f32 *)(BASE(arg0) + 0x9B8), sp10, sp10);
        temp_v0 = BtlChar_GetPos(arg0);
        sceVu0ApplyMatrix(sp50, sp10, (void *)(temp_v0 + 0x70));
        func_00312650(BASE(arg0) + 0x9A0, BASE(arg0) + 0x9A0, sp50);
    }
    func_00312650(sp10, BASE(arg0) + 0x9A0, sp);
    if (func_0029DFD0(sp10) < D_00385A30) {
        func_003126C8(BASE(arg0) + 0x9A0, sp);
    }
    func_00260A50(BASE(arg0));
}
