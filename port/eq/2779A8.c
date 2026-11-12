#include "common.h"

s32 EftWater_GetSurfaceY(f32 *arg0);
f32 StgAmb_Falloff(f32 farg0, f32 farg1, f32 farg2);
void func_00276FD0(f32 farg0);
void sceVu0InversMatrix(s32 arg0, s32 arg1);
extern f32 D_00387070;
extern f32 D_00387074;
extern u8 *D_003876A0;
extern s32 gBtlCamView;

void func_002779A8(void) {
    f32 m[16];
    f32 sp40;
    f32 res;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        func_00276FD0(-64.0f);
        return;
    }
    sceVu0InversMatrix((s32)m, gBtlCamView);
    if (EftWater_GetSurfaceY(&sp40) != 0) {
        if (m[13] < sp40) {
            res = (1.0f - StgAmb_Falloff(-m[13] + sp40, 20.0f, 1200.0f)) + D_00387074;
            if (res >= 1.0f) {
                res = 1.0f;
            }
        } else {
            res = StgAmb_Falloff(m[13] - sp40, 0.0f, 10.0f) * 0.5f;
        }
        func_00276FD0(res);
        return;
    }
    func_00276FD0(D_00387070);
}
