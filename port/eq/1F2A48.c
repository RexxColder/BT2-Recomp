#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 func_00312490(f32 *arg0, f32 *arg1, f32 *arg2);
void sceVu0Normalize(f32 *arg0, f32 *arg1);
void sceVu0UnitMatrix(f32 *arg0);
void sceVu0RotMatrixZ(f32 *arg0, f32 *arg1, f32 arg2);
void sceVu0MulMatrix(f32 *arg0, f32 *arg1, f32 *arg2);

s32 func_001F2A48(f32 *arg0, f32 *arg1, f32 farg0) {
    f32 vB[4];
    f32 vA[4];
    f32 vC[4];
    f32 m[16];

    memset(vB, 0, 0x10);
    vB[1] = 1.0f;
    sceVu0Normalize(vC, arg1);
    if (vC[0] != 0.0f || vC[1] != 0.0f || vC[2] != 0.0f) {
        func_00312490(vA, vB, vC);
        sceVu0Normalize(vA, vA);
        func_00312490(vB, vA, vC);
        sceVu0Normalize(vB, vB);
        sceVu0UnitMatrix(arg0);
        arg0[0] = vA[0];
        arg0[1] = vA[1];
        arg0[2] = vA[2];
        arg0[4] = vB[0];
        arg0[5] = vB[1];
        arg0[6] = vB[2];
        arg0[8] = vC[0];
        arg0[9] = vC[1];
        arg0[10] = vC[2];
        if (farg0 != 0.0f) {
            sceVu0UnitMatrix(m);
            sceVu0RotMatrixZ(m, m, farg0);
            sceVu0MulMatrix(arg0, arg0, m);
        }
        return 1;
    }
    return 0;
}
