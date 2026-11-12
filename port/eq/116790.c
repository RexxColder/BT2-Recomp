#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));

void EftShotFx_UpdateLines(f32 farg0, f32 farg1, f32 farg2, f32 farg3, s32 arg0, void *arg1, void *arg2);
void sceVu0UnitMatrix(f32 *arg0);
void func_0029C8C0(f32 *arg0);
void func_0029D680(f32 *arg0);
f32 atan2f(f32 arg0, f32 arg1);
void func_0029D2D8(void *arg0, f32 *arg1);
void Vu0Cur_StoreMtx(s32 arg0);

void func_00116790(f32 farg0, f32 farg1, f32 farg2, f32 farg3, s32 arg0, u8 *arg1, u8 *arg2) {
    f32 mtx[16];
    f32 v40[4];
    f32 v50[4];
    f32 scale;

    EftShotFx_UpdateLines(farg0, farg1, farg2, farg3, arg0, arg1, arg2);
    scale = farg0 * farg1;
    v40[0] = farg2;
    v40[1] = farg3;
    v40[2] = 0.0f;
    v40[3] = 1.0f;
    func_0029C8C0(v40);
    sceVu0UnitMatrix(mtx);
    mtx[10] = scale;
    mtx[0] = scale;
    mtx[5] = scale;
    func_0029D680(mtx);
    mtx[0] = 1.0f;
    mtx[1] = 0.0f;
    mtx[2] = 0.0f;
    mtx[3] = 0.0f;
    mtx[4] = 0.0f;
    mtx[5] = 0.0f;
    mtx[6] = 0.0f;
    mtx[7] = 0.0f;
    mtx[8] = 0.0f;
    mtx[9] = -1.0f;
    mtx[10] = 0.0f;
    mtx[11] = 0.0f;
    mtx[12] = 0.0f;
    mtx[13] = 0.0f;
    mtx[14] = 0.0f;
    mtx[15] = 1.0f;
    func_0029D680(mtx);
    v50[0] = 0.0f;
    v50[1] = atan2f(*(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x00));
    v50[2] = 0.0f;
    v50[3] = 0.0f;
    func_0029D2D8(D_002C3630, v50);
    v40[3] = 1.0f;
    v40[2] = -*(f32 *)(arg2 + 0x8);
    v40[1] = -*(f32 *)(arg2 + 0x4);
    v40[0] = -*(f32 *)(arg2 + 0x0);
    func_0029C8C0(v40);
    Vu0Cur_StoreMtx(arg0);
}
