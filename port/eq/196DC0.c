#include "common.h"

void sceVu0UnitMatrix(void *arg0);
void sceVu0RotMatrixY(f32 farg0, void *arg1, void *arg2);
void sceVu0ApplyMatrix(void *arg0, void *arg1, void *arg2);
void sceVu0MulMatrix(void *arg0, void *arg1, void *arg2);
void sceVu0TransMatrix(void *arg0, void *arg1, void *arg2);
void func_00196F20(f32 farg0, void *arg1, void *arg2);
void func_001EC310(void *arg0, void *arg1);
extern u8 D_0036E980[] __attribute__((section(".data")));
extern f32 D_00384CBC;

void func_00196DC0(s32 arg0) {
    f32 m[16];
    f32 m40[16];
    f32 m80[16];
    f32 mD0[16];
    s64 spC[2];
    u8 *s1;
    f32 temp_f3;
    f32 temp_f4;
    f32 f2;

    s1 = (u8 *)arg0 + 0xA10;
    spC[0] = *(s64 *)(D_0036E980 + 0);
    spC[1] = *(s64 *)(D_0036E980 + 8);
    sceVu0UnitMatrix(m);
    sceVu0UnitMatrix(m40);
    sceVu0UnitMatrix(m80);
    temp_f4 = *(f32 *)(s1 + 0x80);
    temp_f3 = *(f32 *)(s1 + 0x8C);
    m[0] = m[0] * temp_f4;
    if (temp_f4 < temp_f3) {
        f2 = m[5] * temp_f3;
    } else {
        f2 = m[5] * temp_f4;
    }
    m[5] = f2;
    m[10] = m[10] * *(f32 *)(s1 + 0x80);
    sceVu0RotMatrixY(*(f32 *)(s1 + 0x9C), m40, m40);
    if (*(s32 *)(s1 + 0xB0) & 0x1000) {
        sceVu0UnitMatrix(mD0);
        sceVu0RotMatrixY(*(f32 *)(s1 + 0xA4), mD0, mD0);
        sceVu0ApplyMatrix(spC, mD0, spC);
        func_00196F20(D_00384CBC, m80, spC);
    }
    sceVu0MulMatrix(m40, m80, m40);
    sceVu0MulMatrix(m, m, m40);
    sceVu0TransMatrix(m, m, (u8 *)arg0 + 0xB30);
    func_001EC310(s1, m);
}
