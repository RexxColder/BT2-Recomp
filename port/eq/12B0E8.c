#include "common.h"

void sceVu0ApplyMatrix(f32 *out, s64 *in, f32 *m);
void func_003125D0(void *arg0, void *arg1, f32 farg0);
extern s64 D_0036D990[] __attribute__((section(".data")));

void func_0012B0E8(void *arg0, f32 *arg1, f32 farg0) {
    s64 spT[8];
    s64 sp40[8];
    f32 mat[16];
    f32 sq;
    s32 i;

    for (i = 0; i < 16; i++) {
        mat[i] = arg1[i];
    }
    for (i = 0; i < 8; i++) {
        spT[i] = D_0036D990[i];
    }
    for (i = 0; i < 8; i++) {
        *(s64 *)&sp40[i] = *(s64 *)&mat[2 * i];
    }

    sq = farg0 * farg0;
    mat[0] = sq * farg0;
    mat[1] = sq;
    mat[2] = farg0;
    mat[3] = 1.0f;

    sceVu0ApplyMatrix(mat, spT, mat);
    sceVu0ApplyMatrix(mat, sp40, mat);
    func_003125D0(arg0, mat, 2.0f);
    *(f32 *)((u8 *)arg0 + 0xC) = 1.0f;
}
