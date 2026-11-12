#include "common.h"

void EftShotFx_UpdateLines(s64 arg0, f32 farg0);
void sceVu0UnitMatrix(void *m);
void Vu0Cur_StoreMtx(void *m);
void sceVu0InversMatrix(void *dst, void *src);
void func_0029D2D8(void *arg0, void *arg1);
extern s64 D_00376790[2] __attribute__((section(".data")));
extern u8 D_002C3630[] __attribute__((section(".data")));
extern void *D_00387A44;

void func_00268D50(s32 arg0, u8 *arg1, f32 farg0) {
    f32 sp[16] __attribute__((aligned(8)));
    s64 sp40[2];

    *(f32 *)(arg1 + 0x20) = *(f32 *)((u8 *)D_00387A44 + 0xE540);
    *(f32 *)(arg1 + 0x24) = *(f32 *)((u8 *)D_00387A44 + 0xE544) + 1000.0f;
    *(f32 *)(arg1 + 0x2C) = 1.0f;
    *(f32 *)(arg1 + 0x28) = *(f32 *)((u8 *)D_00387A44 + 0xE548);
    sceVu0UnitMatrix(sp);
    sp[5] = -1.0f;
    sp40[0] = D_00376790[0];
    sp40[1] = D_00376790[1];
    EftShotFx_UpdateLines(D_00376790[0], farg0);
    func_0029D2D8(D_002C3630, sp40);
    Vu0Cur_StoreMtx(sp);
    /* row 3 of the matrix (sp[12..14]) is overwritten with the position */
    sp[12] = *(f32 *)(arg1 + 0x20);
    sp[13] = *(f32 *)(arg1 + 0x24);
    sp[14] = *(f32 *)(arg1 + 0x28);
    sceVu0InversMatrix(arg1 + 0x40, sp);
}
