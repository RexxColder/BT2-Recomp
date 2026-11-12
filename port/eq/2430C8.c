#include "common.h"

extern f32 D_00386D48;
extern f32 D_00386D4C;
extern f32 D_00386D50;
extern f32 D_00386D54;

s32 BtlStage_IsReady(void);
void Rigid_SetVelocity(s32 arg0, f32 *arg1, void *arg2);
s32 StgRigid_Find(s32 arg0);
void func_003126C8(f32 *arg0, s32 arg1);
s32 rand(void);
f32 sceVu0InnerProduct(f32 *arg0, f32 *arg1);

void StgRigid_Launch(s32 arg0, s32 arg1, s32 arg2) {
    f32 sp[8];
    f32 *var_s3;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 var_f20;
    f32 var_f21;
    s32 var_s0;
    s32 var_a0;

    var_s0 = arg0;
    var_f20 = D_00386D48;
    sp[4] = ((f32)rand() / var_f20) * D_00386D4C;
    sp[5] = ((f32)rand() / var_f20) * D_00386D50;
    temp_f0 = (f32)rand();
    var_s3 = &sp[4];
    sp[7] = 1.0f;
    sp[6] = (temp_f0 / var_f20) * -0.25f;
    /* sp[0..3] receives the copies made before the memset (sd of sp+0x10 and sp+0x18) */
    sp[0] = sp[4];
    sp[1] = sp[5];
    sp[2] = sp[6];
    sp[3] = sp[7];
    sp[4] = 0.0f;
    sp[5] = 0.0f;
    sp[6] = 0.0f;
    sp[7] = 0.0f;
    sp[7] = 1.0f;
    var_s0 = StgRigid_Find(var_s0);
    if (var_s0 == 0) {
        BtlStage_IsReady();
        return;
    }
    func_003126C8(var_s3, arg1);
    sp[5] = 0.0f;
    temp_f0_2 = sceVu0InnerProduct(var_s3, var_s3);
    if (temp_f0_2 > 1200.0f) {
        temp_f2 = 1200.0f / temp_f0_2;
        sp[6] *= temp_f2;
        sp[4] *= temp_f2;
    }
    if (arg2 == 1) {
        var_f20 = -17.0f;
    } else if (arg2 == 2) {
        var_f20 = -21.0f;
    } else if (arg2 == 3) {
        var_f20 = -10.0f;
        sp[0] = 0.0f;
        sp[1] = 0.0f;
        sp[2] = 0.0f;
    } else {
        var_f20 = -10.0f;
    }
    var_f21 = D_00386D54;
    temp_f0_3 = var_f20 * 0.5f;
    sp[5] = (temp_f0_3 * ((f32)rand() / var_f21)) + temp_f0_3;
    if (rand() & 1) {
        sp[0] = -sp[0];
    }
    if (rand() & 1) {
        sp[1] = -sp[1];
    }
    if (rand() & 1) {
        sp[2] = -sp[2];
    }
    if (rand() & 1) {
        sp[4] += sp[4] * ((f32)rand() / var_f21);
    }
    if (rand() & 1) {
        sp[5] += sp[5] * ((f32)rand() / var_f21);
    }
    var_a0 = var_s0 + 0x10;
    if (rand() & 1) {
        sp[6] += sp[6] * ((f32)rand() / var_f21);
        var_a0 = var_s0 + 0x10;
    }
    Rigid_SetVelocity(var_a0, var_s3, sp);
}
