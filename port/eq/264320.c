#include "common.h"

u8 *func_00269A40(u8 *arg0, s32 arg1);
f32 func_0025B738(u8 *arg0);
void func_002642D0(u8 *arg0);
s32 func_00264020(u8 *arg0);
void func_00263D00(f32 farg0, u8 *arg1, f32 farg2);
void func_00263DA8(f32 farg0, u8 *arg1, f32 farg2);
void func_00263E60(u8 *arg0);
void func_00263ED0(u8 *arg0, u8 *arg1, u8 *arg2);
s32 ColBox_ContainsPoint(u8 *arg0, u8 *arg1);
void sceVu0InversMatrix(u8 *arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_00386E9C;
extern u8 *D_003876A0;
extern s32 gBtlCamView;

void func_00264320(u8 *arg0, s32 arg1, f32 farg0) {
    u8 fr[0x40];
    u8 *temp_s0;
    u8 *temp_s2;
    s32 var_a1;

    temp_s2 = arg0 + 0xAF0;
    temp_s0 = *(u8 **)(arg0 + 0xB80);
    memset(temp_s0, 0, 0x40);
    *(s32 *)(temp_s0 + 0) = *(s32 *)(arg0 + 0xAF0);
    if (*(s32 *)(*(u8 **)(arg0 + 0x44)) & 0x200000) {
        var_a1 = 0;
    } else {
        var_a1 = 0x2E;
    }
    *(f32 *)(temp_s0 + 0x3C) = func_0025B738(func_00269A40(arg0, var_a1) + 0x30);
    func_002642D0(arg0);
    if (*(s32 *)temp_s0 & 2) {
        if (func_00264020(arg0) == 0) {
            if (!(*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 46))) {
                if (arg1 == 0x63) {
                    sceVu0InversMatrix(fr, gBtlCamView);
                    if (ColBox_ContainsPoint(arg0 + 0xF90, fr + 0x30) != 0) {
                        goto block_8;
                    }
                    goto block_12;
                }
                if ((farg0 < D_00386E9C) && (arg1 == *(s32 *)arg0)) {
                    *(s32 *)temp_s0 = (*(s32 *)temp_s0 & 0xFF00FFFF) | 0x200000;
                }
            }
block_12:
            func_00263D00(*(f32 *)(temp_s2 + 0xAC), temp_s0, *(f32 *)(temp_s2 + 0xB0));
            func_00263ED0(arg0, arg0 + 0xE90, temp_s0);
            func_00263E60(temp_s0);
            if (*(s32 *)(*(u8 **)(arg0 + 0x44)) & 1) {
                func_00263DA8(*(f32 *)(temp_s2 + 0xB4), temp_s0, *(f32 *)(temp_s2 + 0xB8));
                return;
            }
            *(f32 *)(temp_s0 + 0x38) = 128.0f;
        } else {
block_8:
            *(s32 *)temp_s0 = *(s32 *)temp_s0 & ~2;
        }
    }
}
