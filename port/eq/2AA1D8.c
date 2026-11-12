#include "common.h"

void EftShotFx_UpdateLines(void);
void func_0029C8C0(f32 *vec);
void func_0029D680(f32 *mtx);
void func_0029D2D8(void *a0, s32 *a1);
void sceVu0UnitMatrix(f32 *mtx);
void Vu0Cur_StoreMtx(s32 arg0);
f32 atan2f(f32 y, f32 x);
extern u8 D_002C3630[] __attribute__((section(".data")));

void func_002AA1D8(s32 arg0, f32 *arg1, f32 *arg2, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 mtx[16];
    f32 vec[4];
    s32 ints[4];
    f32 temp;

    EftShotFx_UpdateLines();
    vec[0] = farg2;
    vec[1] = farg3;
    vec[2] = 0.0f;
    vec[3] = 1.0f;
    func_0029C8C0(vec);
    sceVu0UnitMatrix(mtx);
    temp = farg0 * farg1;
    mtx[0] = temp;
    mtx[5] = temp;
    mtx[10] = temp;
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
    if (arg1 != NULL) {
        ints[0] = 0;
        atan2f(arg1[8], arg1[0]);
        ints[1] = 0;
        ints[2] = 0;
        ints[3] = 0;
        func_0029D2D8(D_002C3630, ints);
    }
    if (arg2 != NULL) {
        vec[3] = 1.0f;
        vec[2] = -arg2[2];
        vec[1] = -arg2[1];
        vec[0] = -arg2[0];
        func_0029C8C0(vec);
    }
    Vu0Cur_StoreMtx(arg0);
}
