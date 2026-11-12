#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void Vec4_Set(f32 farg0, f32 farg1, f32 farg2, f32 farg3, void *arg4);
s32 func_001D6FF0(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  f32 st0, f32 st1, f32 st2, f32 st3, f32 st4);
void func_00208798(s32 arg0, void *arg1);
s32 rand(void);

extern f32 D_003852C8;
extern f32 D_003852CC;
extern f32 D_003852D0;
extern f32 D_003852D4;
extern f32 D_003852D8;
extern u8 *D_00387E9C;

s32 func_001CF628(s32 arg0, s32 arg1) {
    f32 vec30[4];
    f32 vec40[4];
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f23;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_s1;
    s32 var_v0;

    var_v0 = 0;
    if (D_00387E9C[0x1491] != 0) {
        var_s1 = 0;
        temp_f31 = 360.0f / (f32)arg1;
        temp_f30 = ((f32)rand() / D_003852C8) * 360.0f;
        if (arg1 > 0) {
            temp_f25 = D_003852CC;
            temp_f29 = D_003852C8;
            do {
                func_00208798(arg0, vec30);
                vec30[1] = vec30[1] - (BtlCharApi_GetHeight(arg0) * temp_f25 * D_003852D0);
                temp_f27 = D_003852D4;
                temp_f22 = ((f32)rand() / temp_f29) + 4.0f;
                temp_f21 = ((f32)rand() / temp_f29) + 2.0f;
                temp_f20 = (((f32)rand() / temp_f29) * 8.0f) + 11.0f;
                rand();
                temp_f26 = temp_f30 + (temp_f31 * (f32)var_s1);
                temp_f23 = (((f32)rand() / temp_f29) * 6.0f) + 24.0f;
                temp_f22_2 = temp_f22 * (BtlCharApi_GetHeight(arg0) * temp_f25);
                temp_f21_2 = temp_f21 * (BtlCharApi_GetHeight(arg0) * temp_f25);
                temp_f20_2 = temp_f20 * (BtlCharApi_GetHeight(arg0) * temp_f25);
                temp_f27_2 = BtlCharApi_GetHeight(arg0) * temp_f25 * temp_f27;
                if ((rand() & 1) != 0) {
                    Vec4_Set(0.0f, 0.0f, 1.0f, 1.0f, vec40);
                } else {
                    Vec4_Set(1.0f, 0.0f, 0.0f, 1.0f, vec40);
                }
                temp_f0 = ((rand() & 1) != 0) ? 1.5f : -1.5f;
                var_s1 += 1;
                func_001D6FF0(vec30, vec40, 0x80, 0x80, 0x80, 0xB, 0,
                              temp_f22_2, -7.5f, temp_f21_2, temp_f20_2, D_003852D8, temp_f26, temp_f23, -7.0f,
                              0.0f, temp_f0, temp_f27_2, 0.0f, 1.0f);
            } while (var_s1 < arg1);
        }
        var_v0 = 1;
    }
    return var_v0;
}
