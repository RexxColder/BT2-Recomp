#include "common.h"

f32 BtlCharApi_GetHeight(s32 a0);
f32 Mathf_Cos(f32 farg0);
void Vec3_Normalize(void *a, void *b);
void Vec3_Cross(void *a, void *b, void *c);
void func_00129B28(void *a, void *b, void *c);
void func_00129B58(void *a, void *b, void *c);
void func_00129BB8(f32 farg0, void *a, void *b);
f32 func_00129E08(void *a);
f32 func_0012A3F8(f32 farg0);
f32 func_001775A0(s32 a0, void *a1, void *a2);
void func_00208BE0(s32 a0, void *a1, s64 a2, s32 a3);
void func_00208DE8(s32 a0, void *a1, s32 a2);
s32 rand(void);
extern s64 D_0036E820[2] __attribute__((section(".data")));
extern s32 D_0036E7C0[] __attribute__((section(".data")));
extern f32 D_00384918;
extern f32 D_0038491C;
extern f32 D_00384920;
extern f32 D_00384924;
extern f32 D_00384928;
extern s32 D_00387E94;

s32 func_001768A8(s32 arg0) {
    s32 m[4];
    s64 sp10[2];
    s64 sp20[2];
    s64 sp30[2];
    s64 sp40[2];
    s64 sp50[2];
    s64 sp60[2];
    s64 sp70[2];
    u32 sp80;
    s32 *var_fp;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f28;
    f32 temp_f31;
    f32 temp_f27;
    f32 var_f25;
    s32 temp_a2;
    s32 temp_s0;
    s32 var_s4;
    s32 var_v0;
    u32 temp_v0;
    f32 h;

    var_v0 = 0;
    var_f25 = 0.0f;
    sp40[0] = D_0036E820[0];
    sp40[1] = D_0036E820[1];
    if (D_00387E94 != 0) {
        temp_f28 = D_00384918;
        temp_f31 = D_0038491C;
        func_00208BE0(arg0, sp30, D_0036E820[1], D_00387E94);
        func_00129BB8(-1.0f, sp20, sp30);
        temp_f27 = D_00384920;
        Vec3_Normalize(sp20, sp20);
        Vec3_Cross(sp60, sp20, sp40);
        sp80 = 0;
        Vec3_Normalize(sp60, sp60);
        Vec3_Cross(sp50, sp20, sp60);
        Vec3_Normalize(sp50, sp50);
        var_fp = &D_0036E7C0[0];
        do {
            func_00208DE8(arg0, sp10, var_fp[0]);
            temp_a2 = var_fp[1];
            if (temp_a2 >= 0) {
                func_00208DE8(arg0, sp70, temp_a2);
                func_00129B58(sp70, sp70, sp10);
                temp_f0 = func_00129E08(sp70);
                if (temp_f0 > 6.0f) {
                    var_f25 = temp_f0 / 6.0f;
                }
            }
            temp_f21 = ((f32)rand() / temp_f28) * temp_f31;
            temp_f22 = ((f32)rand() / temp_f28) + 0.0f;
            temp_f20 = Mathf_Cos(temp_f21);
            h = BtlCharApi_GetHeight(arg0);
            func_00129BB8(temp_f20 * temp_f22 * (h * temp_f27), sp30, sp60);
            func_00129B28(m, sp10, sp30);
            temp_f20_2 = func_0012A3F8(temp_f21);
            h = BtlCharApi_GetHeight(arg0);
            func_00129BB8(temp_f20_2 * temp_f22 * (h * temp_f27), sp30, sp50);
            func_00129B28(m, m, sp30);
            temp_s0 = rand();
            h = BtlCharApi_GetHeight(arg0);
            func_00129BB8((((f32)temp_s0 / temp_f28) * 5.0f + 1.5f) * (h * temp_f27), sp30, sp20);
            func_00129B28(m, m, sp30);
            temp_f0_2 = func_001775A0(arg0, m, sp20);
            if (var_f25 > 0.0f) {
                var_s4 = 0;
                if ((s32)var_f25 > 0) {
                    f32 temp_f24 = D_00384924;
                    f32 temp_f23 = D_00384928;
                    do {
                        var_s4 += 1;
                        temp_f21 = ((f32)rand() / temp_f24) * temp_f31;
                        temp_f22 = ((f32)rand() / temp_f24) + 0.0f;
                        temp_f20 = Mathf_Cos(temp_f21);
                        h = BtlCharApi_GetHeight(arg0);
                        func_00129BB8(temp_f20 * temp_f22 * (h * temp_f23), sp30, sp60);
                        func_00129B28(m, sp10, sp30);
                        temp_f20_2 = func_0012A3F8(temp_f21);
                        h = BtlCharApi_GetHeight(arg0);
                        func_00129BB8(temp_f20_2 * temp_f22 * (h * temp_f23), sp30, sp50);
                        func_00129B28(m, m, sp30);
                        temp_s0 = rand();
                        h = BtlCharApi_GetHeight(arg0);
                        func_00129BB8((((f32)temp_s0 / temp_f24) * 5.0f + 1.5f) * (h * temp_f23), sp30, sp20);
                        func_00129B28(m, m, sp30);
                        func_001775A0(arg0, m, sp20);
                    } while (var_s4 < (s32)var_f25);
                }
            }
            temp_v0 = sp80 + 1;
            sp80 = temp_v0;
            var_fp += 2;
        } while (temp_v0 < 0xBU);
        var_v0 = 1;
    }
    return var_v0;
}
