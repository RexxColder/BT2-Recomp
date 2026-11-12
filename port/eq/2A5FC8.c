#include "common.h"

extern u8 D_003B26B0[] __attribute__((section(".data")));
extern f32 D_003872D0;

f32 Gsc_GetFloat(void);
s32 Gsc_GetInt(void);
s32 Gsc_GetIntOr(s32 def);
void StgDbg_PickRandomPlace(void *a0, f32 *a1);
void func_00261108(s32 a0, s32 a1);
void func_002611E8(s32 a0, s32 a1);
void func_00261250(s32 a0, s32 a1);
void func_00261310(s32 a0, s32 a1);
void func_00261378(s32 a0, void *a1);
void func_002613F8(s32 a0, f32 *a1);
void func_00261468(s32 a0, s32 a1, s32 a2);
void func_00261A08(s32 a0);
void func_00272CB0(s32 a0, void *a1, f32 *a2);
void func_00272CC8(void *a0, f32 *a1);
s32 func_002A0010(s32 a0);
void func_002A3D90(f32 f, s32 a0, s32 a1);
void func_002A4118(s32 a0, s32 a1);
s32 func_002AD3E8(s32 a0, s32 a1);

s32 func_002A5FC8(s32 arg0) {
    f32 fr[8];
    s32 s1 = 1;
    s32 s4;
    s32 s5;
    s32 s3;
    s32 s2;

    if (arg0 == 0) {
        s4 = Gsc_GetInt();
        s5 = Gsc_GetInt();
        func_002A0010(0x7A);
        s3 = Gsc_GetIntOr(0x3E8);
        s2 = Gsc_GetIntOr(0x3E9);
        if (func_002A0010(0x66) != 0) {
            s32 want = Gsc_GetInt();
            s32 idx = 0;
            s32 val = *(s32 *)(D_003B26B0 + 0x2B0);

            while (val != want) {
                idx += 1;
                if (!(idx < 5)) {
                    break;
                }
                val = *(s32 *)(D_003B26B0 + idx * 0x10 + 0x2B0);
            }
            if (val == want) {
                s1 = 0;
            }
        }
        if ((s4 >= 0) && (func_002AD3E8(s3, s2) == 0)) {
            if (s1 != 0) {
                s1 = s4 & 0xFFFF;
                func_00261108(s5 & 0xFFFF, s1);

                if (func_002A0010(0x50) != 0) {
                    s32 v = Gsc_GetInt();

                    if (v == 0x20) {
                        func_00272CC8(fr, fr + 4);
                    } else if ((v >= 0x20) && (v < 0x23)) {
                        StgDbg_PickRandomPlace(fr, fr + 4);
                    } else {
                        func_00272CB0(v, fr, fr + 4);
                    }
                    func_00261378(s1, fr);
                    func_002613F8(s1, fr + 4);
                }
                if (func_002A0010(0x70) != 0) {
                    fr[0] = Gsc_GetFloat();
                    fr[1] = Gsc_GetFloat();
                    fr[2] = Gsc_GetFloat();
                    fr[3] = 1.0f;
                    func_00261378(s1, fr);
                }
                if (func_002A0010(0x72) != 0) {
                    f32 k = D_003872D0;

                    fr[4] = (Gsc_GetFloat() / 180.0f) * k;
                    fr[5] = (Gsc_GetFloat() / 180.0f) * k;
                    fr[6] = (Gsc_GetFloat() / 180.0f) * k;
                    fr[7] = 1.0f;
                    func_002613F8(s1, fr + 4);
                }
                if (func_002A0010(0x6D) != 0) {
                    s32 a = Gsc_GetInt();
                    s32 b = Gsc_GetInt();
                    func_00261468(s1, a, b + 1);
                }
                if (func_002A0010(0x64) != 0) {
                    func_002611E8(s1, 0);
                }
                if (func_002A0010(0x73) != 0) {
                    func_00261250(s1, 0);
                }
                func_002A0010(0x48);
                if (func_002A0010(0x74) != 0) {
                    func_00261310(s1, 1);
                }
                if (func_002A0010(0x61) == 0) {
                    func_002A4118(s4, -0x3E8);
                } else {
                    func_002A4118(s4, Gsc_GetInt());
                }
                if (func_002A0010(0x65) != 0) {
                    func_00261A08(s1);
                }
                if (func_002A0010(0x67) == 0) {
                    func_002A3D90(0.0f, s4, 0);
                } else {
                    f32 g = Gsc_GetFloat();

                    func_002A3D90(g, s4, 1);
                }
            }
        }
    }
    return 1;
}
