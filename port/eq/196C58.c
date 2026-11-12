#include "common.h"

void sceVu0UnitMatrix(void *arg0);
void sceVu0RotMatrixX(f32 farg0, void *arg1, void *arg2);
void sceVu0RotMatrix(void *arg0, void *arg1, void *arg2);
void sceVu0MulMatrix(void *arg0, void *arg1, void *arg2);
void sceVu0TransMatrix(void *arg0, void *arg1, void *arg2);
void func_0012AD78(f32 farg0, void *arg1, s32 arg2);
void func_001EC310(void *arg0, void *arg1);
f32 sinf(f32 farg0);
extern f32 D_00384CB4;
extern f32 D_00384CB8;

void func_00196C58(void *arg0) {
    f32 sp[16];
    f32 sp40[16];
    f32 sp80[16];
    f32 vec[4];
    f32 temp_f3;
    f32 temp_f4;
    f32 var_f2;
    f32 temp_f0;
    s32 temp_s0;
    u8 *a;

    a = (u8 *)arg0;
    temp_s0 = (s32)(a + 0xA10);
    sceVu0UnitMatrix(sp);
    sceVu0UnitMatrix(sp40);
    sceVu0UnitMatrix(sp80);
    temp_f4 = *(f32 *)(temp_s0 + 0x80);
    temp_f3 = *(f32 *)(temp_s0 + 0x8C);
    sp[0] = sp[0] * temp_f4;
    if (temp_f4 < temp_f3) {
        var_f2 = sp[5] * temp_f3;
    } else {
        var_f2 = sp[5] * temp_f4;
    }
    sp[5] = var_f2;
    sp[10] = sp[10] * *(f32 *)(temp_s0 + 0x80);
    if (!(*(s32 *)(a + 0xB70) & 0x1000)) {
        sceVu0RotMatrixX(D_00384CB4, sp80, sp80);
        func_0012AD78(*(f32 *)(temp_s0 + 0x9C), sp40, (s32)(a + 0xB50));
        sceVu0MulMatrix(sp40, sp40, sp80);
        sceVu0MulMatrix(sp, sp40, sp);
    } else {
        temp_f0 = *(f32 *)(temp_s0 + 0xA4);
        vec[0] = 0.0f;
        vec[1] = temp_f0;
        vec[2] = sinf(temp_f0) * D_00384CB8;
        vec[3] = 1.0f;
        sceVu0RotMatrix(sp40, sp40, vec);
        sceVu0MulMatrix(sp, sp40, sp);
    }
    sceVu0TransMatrix(sp, sp, a + 0xB30);
    func_001EC310((void *)temp_s0, sp);
}
