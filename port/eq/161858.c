#include "common.h"

void Mtx_RotateXYZ(void *arg0, void *arg1, f32 *arg2);
void Mtx_StoreIdentity(void *arg0);
void Mtx_Translate(void *arg0, void *arg1, void *arg2);
void Vec3_Add(f32 *arg0, f32 *arg1, void *arg2);
void func_00128C58(f32 farg0, void *arg0, void *arg1);
void func_00129C28(void *arg0, void *arg1);
void func_00161800(void *arg0, void *arg1);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDD40(s32 arg0, void *arg1);
extern f32 D_00384740;
extern f32 D_00384744;
extern f32 D_00384748;

void func_00161858(u8 *arg0) {
    f32 *temp_s2;
    f32 *var_v0_3;
    f32 temp_f0;
    f32 var_f0;
    s32 temp_a1;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 temp_v0_2;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s1;
    u8 *var_s3;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)temp_s0 & 5) {
        *(s32 *)(temp_s0 + 4) = *(s32 *)(temp_s0 + 4) & ~8;
    }
    temp_a1 = *(s32 *)(temp_s0 + 4);
    temp_s1 = temp_s0 + 0xA70;
    if (temp_a1 & 1) {
        var_v1 = *(s32 *)(temp_s1 + 0x34);
        var_v0 = temp_a1 & 8;
        if (!(var_v1 & 1)) {
            func_00161800(arg0, temp_s1);
            temp_v0 = *(s32 *)(temp_s1 + 0x34) | 1;
            *(s32 *)(temp_s1 + 0x34) = temp_v0;
            var_v1 = temp_v0;
            var_v0 = *(s32 *)(temp_s0 + 4) & 8;
        }
        temp_v0_2 = var_v1 & 2;
        if (var_v0 != 0) {
            var_s3 = temp_s1 + 0x40;
            if (temp_v0_2 == 0) {
                func_001EDBD8(*(s32 *)(temp_s1 + 0x30), 1);
                var_v0_2 = *(s32 *)(temp_s1 + 0x34) | 2;
                goto block_10;
            }
            goto block_11;
        }
        if (temp_v0_2 != 0) {
            func_001EDBD8(*(s32 *)(temp_s1 + 0x30), 0);
            var_v0_2 = *(s32 *)(temp_s1 + 0x34) & ~2;
block_10:
            *(s32 *)(temp_s1 + 0x34) = var_v0_2;
            var_s3 = temp_s1 + 0x40;
            if (*(s32 *)(temp_s1 + 0x34) & 2) {
block_11:
                temp_s2 = (f32 *)(temp_s1 + 0x50);
                func_00129C28(var_s3, temp_s0 + 0x40);
                Vec3_Add(temp_s2, temp_s2, temp_s1 + 0x60);
                var_v0_3 = temp_s2;
                var_v1_2 = 2;
                do {
                    temp_f0 = *var_v0_3;
                    if (D_00384740 < temp_f0) {
                        var_f0 = temp_f0 - D_00384744;
                        goto block_16;
                    }
                    if (temp_f0 < D_00384748) {
                        var_f0 = temp_f0 + D_00384744;
block_16:
                        *var_v0_3 = var_f0;
                    }
                    var_v1_2 -= 1;
                    var_v0_3 += 1;
                } while (var_v1_2 >= 0);
                temp_s0_2 = temp_s1 + 0x70;
                Mtx_StoreIdentity(temp_s0_2);
                func_00128C58(*(f32 *)(temp_s1 + 0x38), temp_s0_2, temp_s0_2);
                Mtx_RotateXYZ(temp_s0_2, temp_s0_2, temp_s2);
                Mtx_Translate(temp_s0_2, temp_s0_2, var_s3);
                func_001EDD40(*(s32 *)(temp_s1 + 0x30), temp_s0_2);
            }
        }
    }
}
