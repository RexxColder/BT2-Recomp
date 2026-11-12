#include "common.h"

s32 rand(void);
f32 EftMath_WrapAngle(f32 farg0);
f32 Mathf_Cos(f32 farg0);
void Vec4_Set(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 *arg4);
f32 func_0012A3F8(f32 farg0);
void func_001D4678(s32 arg0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 st0, f32 st1, f32 st2, f32 st3);

extern f32 D_00385260;
extern f32 D_00385264;
extern f32 D_00385268;
extern f32 D_0038526C;
extern f32 D_00385270;
extern f32 D_00385274;
extern f32 D_00385278;
extern u8 *D_00387E9C;

s32 func_001CE818(s32 arg0, f32 farg0) {
    f32 vec20[4];
    f32 vec30[4];
    f32 vec40[4];
    f32 sp54;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f23;
    f32 temp_f23_2;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f30;
    f32 temp_f18;
    s32 temp_v0;
    s32 temp_a2;
    s32 temp_a1;
    s32 v1;
    s32 r;
    s32 i;
    s32 var_v0;

    var_v0 = 0;
    if (D_00387E9C[0x1491] != 0) {
        i = 0;
        temp_f27 = D_00385260;
        temp_f30 = D_00385268;
        sp54 = ((f32)rand() / D_00385260) * D_00385264;
        do {
            temp_f28 = D_00385270;
            temp_f0 = EftMath_WrapAngle(sp54 + (D_0038526C * (f32)i));
            vec20[0] = func_0012A3F8(temp_f0);
            vec20[1] = 0.0f;
            vec20[2] = Mathf_Cos(temp_f0);
            vec20[3] = 1.0f;
            temp_f24 = (((f32)rand() / temp_f27) * 0.5f) + D_00385274;
            temp_f23 = (((f32)rand() / temp_f27) * 1.5f) + 2.0f;
            temp_f22 = (((f32)rand() / temp_f27) * temp_f30) + 0.5f;
            temp_f0_2 = farg0 * D_00385278;
            temp_f28_2 = temp_f0_2 * temp_f28;
            temp_f24_2 = temp_f24 * temp_f0_2;
            temp_f23_2 = temp_f23 * temp_f0_2;
            temp_f22_2 = temp_f22 * temp_f0_2;
            temp_f26 = (((f32)rand() / temp_f27) * temp_f30) + 0.5f;
            Vec4_Set(128.0f, 128.0f, 128.0f, 0.0f, vec30);
            temp_v0 = rand();
            temp_a2 = temp_v0 + 0x1F;
            temp_a1 = temp_v0 < 0;
            v1 = (temp_a1 != 0) ? temp_a2 : temp_v0;
            r = temp_v0 - (((v1) >> 5) << 5);
            Vec4_Set(128.0f, 128.0f, 128.0f, (f32)(0x80 - r), vec40);
            temp_f20 = ((f32)rand() / temp_f27) * 360.0f;
            temp_f18 = ((rand() & 1) != 0) ? 1.5f : -1.5f;
            i += 1;
            func_001D4678(0, arg0, (s32)vec20, (s32)vec30, (s32)vec40, 0, 0xB, 0,
                          temp_f24_2, -2.0f, temp_f23_2, temp_f22_2, temp_f23_2 * 2.5f, temp_f20, temp_f18, temp_f28_2,
                          0.0f, temp_f26, 0.0f, 1.0f);
            var_v0 = 1;
        } while (i < 3);
    }
    return var_v0;
}
