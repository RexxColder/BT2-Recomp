#include "m2c_macros.h"

void Mtx_InverseRT(f32 *arg0, s32 arg1);
void EftWater_GetSurfaceY(f32 *arg0);
extern s32 gBtlCamView;

s32 func_001420F0(void) {
    f32 mtx[16];
    f32 sp40;

    sp40 = 0.0f;
    Mtx_InverseRT(mtx, gBtlCamView);
    EftWater_GetSurfaceY(&sp40);
    return (sp40 <= mtx[13]) ? 1 : 0;
}
