#include "common.h"
#include "m2c_macros.h"

s32 BtlCharApi_IsInTechnique();                  /* extern */
s32 BtlScene_IsEffectStopped();              /* extern */
M2C_UNK BtlTask_SetDead();                    /* extern */
f32 EftMath_WrapAngle(f32, s32);                    /* extern */
s32 func_00126EC0();                          /* extern */
s32 func_0020B3D0();                             /* extern */
s32 rand(void);                                   /* extern */
extern f32 D_00384FC8;
extern f32 D_00384FCC;
extern f32 D_00384FD0;
extern f32 D_00384FD4;

void EftRay_Update(void *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_hi_4;
    s32 temp_hi_5;
    s32 temp_hi_6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_v0;
    s32 var_v0_2;
    void *temp_s1;
    void *var_s0;
    void *var_s0_3;
    void *var_s0_4;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    if (BtlScene_IsEffectStopped(M2C_FIELD(temp_s1, s32 *, 0x50C), M2C_FIELD(temp_s1, u8 *, 0x518)) == 0) {
        temp_v0 = M2C_FIELD(temp_s1, s32 *, 0x510);
        if (temp_v0 <= 0) {
            var_a0 = M2C_FIELD(temp_s1, s32 *, 0x514);
            var_v0 = var_a0 & 2;
            if (var_a0 & 1) {
                temp_f0 = M2C_FIELD(temp_s1, f32 *, 0x4E4) - D_00384FC8;
                M2C_FIELD(temp_s1, f32 *, 0x4E4) = temp_f0;
                if (temp_f0 < 0.0f) {
                    temp_v0_2 = var_a0 | 2;
                    M2C_FIELD(temp_s1, f32 *, 0x4E4) = 0.0f;
                    M2C_FIELD(temp_s1, s32 *, 0x514) = temp_v0_2;
                    var_a0 = temp_v0_2;
                    var_v0 = var_a0 & 2;
                }
            }
            var_v0_2 = var_a0 & 8;
            if (var_v0 != 0) {
                temp_f0_2 = M2C_FIELD(temp_s1, f32 *, 0x4E8) - M2C_FIELD(temp_s1, f32 *, 0x4EC);
                M2C_FIELD(temp_s1, f32 *, 0x4E8) = temp_f0_2;
                if (temp_f0_2 < 0.0f) {
                    temp_v1 = var_a0 | 4;
                    M2C_FIELD(temp_s1, f32 *, 0x4E8) = 0.0f;
                    M2C_FIELD(temp_s1, s32 *, 0x514) = temp_v1;
                    if (temp_v1 & 0x10) {
                        temp_v0_3 = var_a0 | 0xC;
                        M2C_FIELD(temp_s1, s32 *, 0x514) = temp_v0_3;
                        var_a0_2 = temp_v0_3;
                    } else {
                        var_a0_2 = temp_v1;
                    }
                    var_v0_2 = var_a0_2 & 8;
                }
            }
            if (var_v0_2 != 0) {
                BtlTask_SetDead(arg0);
                return;
            }
            temp_v1_2 = M2C_FIELD(temp_s1, s32 *, 0x508);
            switch (temp_v1_2) {                    /* irregular */
            case 0:
                temp_f0_3 = M2C_FIELD(temp_s1, f32 *, 0x490) - M2C_FIELD(temp_s1, f32 *, 0x4E0);
                if (temp_f0_3 < 0.0f) {
                    M2C_FIELD(temp_s1, f32 *, 0x490) = 0.0f;
                }
                break;
            case 1:
                temp_hi = rand() % 360;
                var_s0 = temp_s1;
                var_s2 = 0;
                temp_f20 = EftMath_WrapAngle(((f32) temp_hi / 180.0f) * D_00384FCC, temp_hi);
                if (M2C_FIELD(temp_s1, s32 *, 0x4FC) > 0) {
                    do {
                        var_s2 += 1;
                        temp_hi_2 = rand() % (s32) M2C_FIELD(temp_s1, s32 *, 0x4F8);
                        M2C_FIELD(var_s0, s8 *, 3) = (s8) temp_hi_2;
                        M2C_FIELD(var_s0, f32 *, 4) = EftMath_WrapAngle(M2C_FIELD(var_s0, f32 *, 4) + temp_f20, temp_hi_2);
                        var_s0 += 0x18;
                    } while (var_s2 < M2C_FIELD(temp_s1, s32 *, 0x4FC));
                }
                break;
            case 2:
                var_s0_2 = BtlCharApi_IsInTechnique(M2C_FIELD(temp_s1, s32 *, 0x50C));
                if (func_0020B3D0(M2C_FIELD(temp_s1, s32 *, 0x50C)) >= 0) {
                    var_s0_2 += BtlCharApi_IsInTechnique(func_0020B3D0(M2C_FIELD(temp_s1, s32 *, 0x50C)));
                }
                if (var_s0_2 != 0) {
                    M2C_FIELD(temp_s1, f32 *, 0x4E8) = -1.0f;
                    M2C_FIELD(temp_s1, f32 *, 0x4E4) = -1.0f;
                }
                temp_hi_3 = rand() % 360;
                var_s0_3 = temp_s1;
                var_s2_2 = 0;
                temp_f20_2 = EftMath_WrapAngle(((f32) temp_hi_3 / 180.0f) * D_00384FD0, temp_hi_3);
                if (M2C_FIELD(temp_s1, s32 *, 0x4FC) > 0) {
                    do {
                        var_s2_2 += 1;
                        temp_hi_4 = rand() % (s32) M2C_FIELD(temp_s1, s32 *, 0x4F8);
                        M2C_FIELD(var_s0_3, s8 *, 3) = (s8) temp_hi_4;
                        M2C_FIELD(var_s0_3, f32 *, 4) = EftMath_WrapAngle(M2C_FIELD(var_s0_3, f32 *, 4) + temp_f20_2, temp_hi_4);
                        var_s0_3 += 0x18;
                    } while (var_s2_2 < M2C_FIELD(temp_s1, s32 *, 0x4FC));
                }
                break;
            case 3:
                if (func_00126EC0(arg0) != 0) {
                    M2C_FIELD(temp_s1, f32 *, 0x4E8) = -1.0f;
                    M2C_FIELD(temp_s1, f32 *, 0x4E4) = -1.0f;
                }
                temp_hi_5 = rand() % 360;
                var_s0_4 = temp_s1;
                var_s2_3 = 0;
                temp_f20_3 = EftMath_WrapAngle(((f32) temp_hi_5 / 180.0f) * D_00384FD4, temp_hi_5);
                if (M2C_FIELD(temp_s1, s32 *, 0x4FC) > 0) {
                    do {
                        var_s2_3 += 1;
                        temp_hi_6 = rand() % (s32) M2C_FIELD(temp_s1, s32 *, 0x4F8);
                        M2C_FIELD(var_s0_4, s8 *, 3) = (s8) temp_hi_6;
                        M2C_FIELD(var_s0_4, f32 *, 4) = EftMath_WrapAngle(M2C_FIELD(var_s0_4, f32 *, 4) + temp_f20_3, temp_hi_6);
                        var_s0_4 += 0x18;
                    } while (var_s2_3 < M2C_FIELD(temp_s1, s32 *, 0x4FC));
                }
                break;
            }
        } else {
            M2C_FIELD(temp_s1, s32 *, 0x510) = (s32) (temp_v0 - 1);
        }
    }
}
