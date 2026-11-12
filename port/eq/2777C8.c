#include "common.h"

s32 EftWater_GetSurfaceY(f32 *arg0);
void sceVu0InversMatrix(f32 *arg0, s32 arg1);
f32 StgAmb_Falloff(f32 farg0, f32 farg1, f32 farg2);
void func_00276FD0(f32 farg0, s32 arg0, s32 arg1);
extern f32 D_00387064;
extern u8 *D_003876A0;
extern s32 gBtlCamView;

void func_002777C8(s32 arg0) {
    f32 sp[17];
    f32 var_f0;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        func_00276FD0(-64.0f, arg0, gBtlCamView);
        return;
    }
    sceVu0InversMatrix(sp, gBtlCamView);
    if (EftWater_GetSurfaceY(&sp[16]) != 0) {
        if (sp[13] < sp[16]) {
            var_f0 = StgAmb_Falloff(-sp[13] + sp[16], 20.0f, 150.0f);
        } else {
            var_f0 = StgAmb_Falloff(sp[13] - sp[16], 0.0f, 10.0f);
        }
        ((void (*)(f32))func_00276FD0)(var_f0);
        return;
    }
    ((void (*)(f32))func_00276FD0)(D_00387064);
}
