#include "common.h"

void func_00312680(void *arg0, void *arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(void *arg0, void *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 func_0029DFD0(s32 arg0);
f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
s32 func_001FC3B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);

/* 0x001FC5A0 (effect transform). Two paths share the call to func_001FC3B0 at the end:
 * - when the counter at obj+0x298 is positive (or obj+0x2A0 has bit 0x80): the scale f20 is 1 - v1/v0 (v0 = obj+0x29C,
 *   0 when v0 <= 0), three vectors are scaled and transformed from the obj+0x210..0x260 matrices, and the
 *   blended vectors come from obj+0x120..0x134;
 * - otherwise: a direction vector from the angles -obj+0x1A0 and obj+0x1A4 (cos/sin), scaled by the value returned
 *   by func_0029DFD0, and the positions come from func_00312650.
 * The stack args of func_001FC3B0 are the saved caller arguments and obj+0x140 (or -1), and arg7 with bits 0x1 and
 * 0x8 cleared. */
void func_001FC5A0(u8 *obj, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2) {
    u8 *s1 = obj + 0x150;
    f32 vecA[4];
    f32 vecB[4];
    f32 vecC[4];
    f32 vecD[4];
    f32 f20 = 0.0f;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 c1;
    f32 c2;
    f32 c3;
    f32 s1v;
    f32 s2v;
    s32 v0;
    s32 v1;
    s32 s4;
    s32 s5;

    v1 = *(s32 *)(s1 + 0x148);
    if (v1 > 0 || (*(s32 *)(s1 + 0x150) & 0x80) != 0) {
        v0 = *(s32 *)(s1 + 0x14C);
        if (v0 > 0) {
            f20 = 1.0f - ((f32)v1 / (f32)v0);
        }
        func_00312680(vecA, obj + 0x220, f20);
        func_00312638((s32)vecA, (s32)vecA, (s32)(obj + 0x210));
        func_00312680(vecB, obj + 0x240, f20);
        func_00312638((s32)vecB, (s32)vecB, (s32)(obj + 0x230));
        func_00312680(vecC, obj + 0x260, f20);
        func_00312638((s32)vecC, (s32)vecC, (s32)(obj + 0x250));

        s5 = *(s32 *)(s1 + 0x138);
        f23 = *(f32 *)(s1 + 0x120) + *(f32 *)(s1 + 0x124) * f20;
        f24 = *(f32 *)(s1 + 0x128) + *(f32 *)(s1 + 0x12C) * f20;
        f22 = *(f32 *)(s1 + 0x130) + *(f32 *)(s1 + 0x134) * f20;
        s4 = *(s32 *)(s1 + 0x140);
    } else {
        f24 = *(f32 *)(s1 + 0x50);
        f23 = *(f32 *)(s1 + 0x54);
        f21 = -f24;
        func_003126C8(vecB, obj + 0x1B0);
        func_00312650(vecD, obj + 0x1B0, obj + 0x180);
        f22 = func_0029DFD0((s32)vecD);

        c1 = cosf(f21);
        s1v = sinf(f23);
        f20 = c1 * s1v;
        s4 = -1;
        vecD[0] = f20;
        s2v = sinf(f21);
        vecD[1] = s2v;
        c2 = cosf(f21);
        c3 = cosf(f23);
        f20 = c2 * c3;
        vecD[2] = f20;
        func_00312680(vecD, vecD, f22);
        func_00312638((s32)vecA, (s32)(obj + 0x180), (s32)vecD);
        func_003126C8(vecC, vecA);

        s5 = -1;
    }

    func_001FC3B0(obj, (s32)vecA, arg1, (s32)vecB, arg2, (s32)vecC, arg3, s5,
                  arg4, s4, arg5, arg6, arg7 & ~9,
                  f23, farg0, f24, farg1, f22, farg2);
}
