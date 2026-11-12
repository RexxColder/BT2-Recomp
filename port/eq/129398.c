#include "common.h"
#include "vu0_state.h"

/* Vu0Cur_ScaleDiagUniform(f12 s): vf4.x = s; vf16.x, vf17.y, vf18.z *= s. */
void Vu0Cur_ScaleDiagUniform(f32 farg0) {
    gVu0.vf[4][0] = farg0;
    gVu0.vf[16][0] = gVu0.vf[16][0] * gVu0.vf[4][0];
    gVu0.vf[17][1] = gVu0.vf[17][1] * gVu0.vf[4][0];
    gVu0.vf[18][2] = gVu0.vf[18][2] * gVu0.vf[4][0];
}
