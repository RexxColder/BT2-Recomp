#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void func_00208798(s32 arg0, s32 arg1);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 func_001D6FF0(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  f32 st0, f32 st1, f32 st2, f32 st3, f32 st4);
s32 rand(void);
extern f32 D_003853E4;
extern f32 D_003853E8;
extern f32 D_003853EC;
extern f32 D_003853F0;
extern f32 D_003853F4;
extern u8 *D_00387E9C;

s32 func_001D1818(s32 arg0, s32 arg1, f32 farg0, f32 farg1) {
    u8 sp[0x60];   /* tamano de locales del original (antes 0x58) */
    s32 var_s1;
    s32 var_v0;
    s32 r;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f28;
    f32 f29;
    f32 f30;
    f32 f31;
    f32 gh;
    f32 st1;

    *(f32 *)(sp + 0x50) = farg1;
    var_v0 = 0;
    if (D_00387E9C[0x1491] != 0) {
        f31 = 360.0f / (f32)arg1;
        var_s1 = 0;
        f30 = ((f32)rand() / D_003853E4) * 360.0f;
        if (arg1 > 0) {
            f24 = D_003853E8;
            f29 = D_003853E4;
            f28 = 0.0f;
            f26 = 1.0f;
            do {
                func_00208798(arg0, (s32)(sp + 0x30));
                gh = BtlCharApi_GetHeight(arg0);
                *(f32 *)(sp + 0x34) = *(f32 *)(sp + 0x34) - gh * f24 * D_003853EC;
                f22 = ((f32)rand() / f29) + 4.0f;
                f21 = ((f32)rand() / f29) + 2.0f;
                f20 = (((f32)rand() / f29) * 8.0f) + 11.0f;
                rand();
                f25 = f30 + f31 * (f32)var_s1;
                f23 = (((f32)rand() / f29) * 6.0f) + 24.0f;
                gh = BtlCharApi_GetHeight(arg0);
                f22 = f22 * (gh * f24);
                gh = BtlCharApi_GetHeight(arg0);
                f21 = f21 * (gh * f24);
                gh = BtlCharApi_GetHeight(arg0);
                f20 = f20 * (gh * f24);
                gh = BtlCharApi_GetHeight(arg0);
                f27 = (gh * f24) * D_003853F0;

                if ((rand() & 1) != 0) {
                    Vec4_Set((void *)(sp + 0x40), f28, f28, f26, f26);
                } else {
                    Vec4_Set((void *)(sp + 0x40), f26, f28, f28, f26);
                }

                r = rand();
                st1 = ((r & 1) != 0) ? 1.5f : -1.5f;
                var_s1 += 1;
                func_001D6FF0((void *)(sp + 0x30), (void *)(sp + 0x40), 0x80, 0x80, 0x80, 0x0B, 0,
                              f22, -7.5f, f21, f20, D_003853F4, f25, f23, -7.0f,
                              0.0f, st1, f27, 0.0f, farg1);
            } while (var_s1 < arg1);
        }
        var_v0 = 1;
    }
    return var_v0;
}
