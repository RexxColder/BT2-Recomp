#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void sceVu0ApplyMatrix(f32 *out, s64 *in, f32 *m);
void func_003125D0(void *arg0, void *arg1, f32 farg0);
extern s64 D_0036DA10[] __attribute__((section(".data")));

void func_0012B420(void *arg0, f32 *arg1, f32 farg0) {
    s64 spT[8];
    s64 sp40[8];
    s64 spB0[2];
    f32 mat[12];
    f32 sq;
    s32 i;

    for (i = 0; i < 12; i++) {
        mat[i] = arg1[i];
    }
    for (i = 0; i < 8; i++) {
        spT[i] = D_0036DA10[i];
    }
    memset(spB0, 0, 0x10);
    *(s64 *)&sp40[0] = *(s64 *)&mat[0];
    *(s64 *)&sp40[1] = *(s64 *)&mat[2];
    *(s64 *)&sp40[2] = *(s64 *)&mat[4];
    *(s64 *)&sp40[3] = *(s64 *)&mat[6];
    *(s64 *)&sp40[4] = *(s64 *)&mat[8];
    *(s64 *)&sp40[5] = *(s64 *)&mat[10];
    sp40[6] = spB0[0];
    sp40[7] = spB0[1];

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
