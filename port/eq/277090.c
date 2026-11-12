#include "common.h"

/* func_00276FD0 is called with the float only, or with a1 = gBtlCamView (a0 is garbage there): GUESS arity 3 */
s32 EftWater_GetSurfaceY(s32 arg0);
f32 StgAmb_Falloff(f32 farg0, f32 farg1, f32 farg2);
s32 func_00276D00(void);
void func_00276FD0(f32 farg0, s32 arg0, s32 arg1);
s32 sceVu0InversMatrix(f32 farg0, s32 arg0, s32 arg1);
extern f32 D_00387020;
extern u8 *D_003876A0;
extern s32 gBtlCamView;

void func_00277090(void) {
    u8 buf[0x50];   /* tamano de locales del original (antes 0x44) */
    f32 a;
    f32 b;
    f32 falloff;

    if (func_00276D00() == 1) {
        func_00276FD0(D_00387020, 0, 0);
        return;
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        func_00276FD0(-64.0f, 0, gBtlCamView);
        return;
    }
    sceVu0InversMatrix(D_00387020, (s32)buf, gBtlCamView);
    if (EftWater_GetSurfaceY((s32)(buf + 0x40)) != 0) {
        a = *(f32 *)(buf + 0x34);
        b = *(f32 *)(buf + 0x40);
        if (a < b) {
            falloff = StgAmb_Falloff(-a + b, 20.0f, 150.0f);
        } else {
            falloff = StgAmb_Falloff(a - b, 0.0f, 10.0f);
        }
        func_00276FD0(falloff, 0, 0);
    }
}
