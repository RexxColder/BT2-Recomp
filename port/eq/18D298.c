#include "common.h"

#define AT(T, p, off) (*(T *)((u8 *)(p) + (off)))

f32 EftMath_WrapAngle(f32 farg0, s64 arg1, s64 arg2, s64 arg3, s64 arg4, s64 arg5, s64 arg6);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void Mtx_RotateX(f32 farg0, u8 *arg0, u8 *arg1);
void Mtx_RotateY(f32 farg0, u8 *arg0, u8 *arg1);
void Mtx_RotateZ(f32 farg0, u8 *arg0, u8 *arg1);
void Mtx_Translate(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec4_Set(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C50(u8 *arg0, u8 *arg1, u8 *arg2);

void func_0018D298(f32 farg0, u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, s64 arg4, s64 arg5) {
    u8 fr[0x70];
    u8 *s1;
    u8 *s2;
    u8 *s4;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f;
    f32 cc;
    s32 i;
    s32 s7;

    s1 = arg0;
    s2 = arg0 + 0x70;
    s4 = s2;
    f20 = farg0;
    f22 = 0.0f;
    f23 = 1.0f;

    for (i = 0; i < 0x40; i++) {
        fr[i] = arg1[i];
    }
    for (i = 0; i < 0x10; i++) {
        fr[0x40 + i] = arg2[i];
    }
    for (i = 0; i < 0x10; i++) {
        fr[0x50 + i] = arg3[i];
    }

    /* first call: only f12 is written before it; a0..a3, t0, t1 are the function's own args */
    f = EftMath_WrapAngle(AT(f32, s1, 0x68), (s64)arg0, (s64)arg1, (s64)arg2, (s64)arg3, arg4, arg5);
    Mtx_RotateZ(f, fr, fr);
    f = ((f32 (*)(f32))EftMath_WrapAngle)(AT(f32, s1, 0x60));
    Mtx_RotateX(f, fr, fr);
    f = ((f32 (*)(f32))EftMath_WrapAngle)(AT(f32, s1, 0x64));
    Mtx_RotateY(f, fr, fr);

    func_00129BD0(fr + 0x60, s1, f20);
    Mtx_Translate(fr, fr, fr + 0x60);

    f = Mathf_Asin(-AT(f32, fr, 0x54));
    f21 = ((f32 (*)(f32))EftMath_WrapAngle)(f);
    f = atan2f(AT(f32, fr, 0x50), AT(f32, fr, 0x58));
    f20 = ((f32 (*)(f32))EftMath_WrapAngle)(f);
    Mtx_RotateX(f21, fr, fr);
    Mtx_RotateY(f20, fr, fr);
    Mtx_Translate(fr, fr, fr + 0x40);

    cc = AT(f32, s1, 0xCC);
    Vec4_Set(s2, -cc, -cc, f22, f23);
    Vec4_Set(s1 + 0x90, -cc, cc, f22, f23);
    Vec4_Set(s1 + 0x80, cc, -cc, f22, f23);
    Vec4_Set(s1 + 0xA0, cc, cc, f22, f23);

    s7 = 3;
    do {
        s7 -= 1;
        func_00129C50(s4, fr, s4);
        s4 += 0x10;
    } while (s7 >= 0);
}
