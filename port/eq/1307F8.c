#include "common.h"

s32 rand(void);
f32 EftMath_WrapAngle(f32 farg0);
f32 Mathf_Cos(f32 farg0);
f32 func_0012A3F8(f32 farg0);
void sceVu0UnitMatrix(f32 *arg0);
void sceVu0RotMatrixY(f32 farg0, f32 *arg0, f32 *arg1);
void sceVu0ApplyMatrix(u8 *arg0, f32 *arg1, u8 *arg2);
extern f32 D_003841FC;
extern f32 D_00384200;

void func_001307F8(u8 *arg0) {
    f32 sp[16];
    f32 f22;

    f22 = ((f32)rand() / D_003841FC) * D_00384200;
    *(f32 *)(arg0 + 0) = func_0012A3F8(f22);
    *(f32 *)(arg0 + 4) = Mathf_Cos(f22);
    *(f32 *)(arg0 + 8) = 0.0f;
    *(f32 *)(arg0 + 0xC) = 0.0f;
    f22 = ((f32)rand() / D_003841FC) * D_00384200;
    sceVu0UnitMatrix(sp);
    sceVu0RotMatrixY(EftMath_WrapAngle(f22), sp, sp);
    sceVu0ApplyMatrix(arg0, sp, arg0);
}
