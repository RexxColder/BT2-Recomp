#include "common.h"

extern u8 *gBtlCamView;
extern u8 *gEftAuraPrm;

void Mtx_StoreIdentity(f32 *arg0);
void Vec3_Cross(f32 *arg0, f32 *arg1, f32 *arg2);
void Vec3_Normalize(f32 *arg0, f32 *arg1);
void func_00129B58(f32 *arg0, f32 *arg1, f32 *arg2);
void func_00129BD0(f32 *arg0, f32 *arg1, f32 farg0);
void func_00129C38(f32 *arg0, f32 *arg1);
f32 func_00129CD8(f32 *arg0, f32 *arg1);

void func_0017B4D8(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 sp[4];
    f32 sp10[4];
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];
    f32 temp_f0;
    f32 var_f20;

    sp40[0] = *(f32 *)(gBtlCamView + 0x8);
    sp40[1] = *(f32 *)(gBtlCamView + 0x18);
    sp40[2] = *(f32 *)(gBtlCamView + 0x28);
    sp40[3] = 1.0f;
    temp_f0 = func_00129CD8(sp40, arg1);
    if (temp_f0 < 0.0f) {
        var_f20 = -temp_f0 * *(f32 *)(gEftAuraPrm + 0x14);
        func_00129BD0(sp, sp40, -1.0f);
    } else {
        var_f20 = temp_f0 * *(f32 *)(gEftAuraPrm + 0x14);
        func_00129C38(sp, sp40);
    }
    sp[3] = 1.0f;
    func_00129B58(sp, arg1, sp);
    Vec3_Normalize(sp, sp);
    func_00129BD0(sp, sp, var_f20);

    sp30[0] = arg1[0] + sp[0];
    sp30[1] = arg1[1] + sp[1];
    sp30[2] = arg1[2] + sp[2];
    sp30[3] = 1.0f;
    Vec3_Normalize(sp30, sp30);
    Vec3_Cross(sp10, sp40, sp30);
    Vec3_Normalize(sp10, sp10);
    Vec3_Cross(sp20, sp10, sp30);
    Vec3_Normalize(sp20, sp20);

    Mtx_StoreIdentity(arg0);
    arg0[0] = sp10[0];
    arg0[1] = sp10[1];
    arg0[2] = sp10[2];
    arg0[4] = sp20[0];
    arg0[5] = sp20[1];
    arg0[6] = sp20[2];
    arg0[8] = sp30[0];
    arg0[9] = sp30[1];
    arg0[10] = sp30[2];
    arg0[12] = arg2[0];
    arg0[13] = arg2[1];
    arg0[14] = arg2[2];
}
