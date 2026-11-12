#include "common.h"

s32 BtlChar_GetPos(s32 a0);
void func_0020FAD0(f32 f12, f32 f13, s32 a0, s32 a1, s32 a2);
s32 func_002127C0(s32 a0);
s32 BtlChar_FrameMod(s32 a0);
void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern u8 *D_003876A0;
extern f32 D_00385A00;

void func_00210110(s32 arg0) {
    s32 sp[1];
    s32 sp4;
    s32 pos;
    s32 spC;
    s32 sp14;
    s32 sp18;
    s32 j;
    s32 s3;
    s32 s5;
    s32 s0;
    s32 s1;
    s32 t0v;
    s32 quot;
    u8 *s2;
    u8 *s6;
    u8 *fp;
    u8 *sp10;
    s32 proceed;

    pos = BtlChar_GetPos(arg0);
    spC = 0;
    sp18 = 0;
    s6 = (u8 *)arg0 + 0x4F0;
    func_0020FAD0(200.0f, D_00385A00, pos, (s32)sp, (s32)&sp4);
    fp = (u8 *)arg0 + 0x360;
    do {
        if (*(s8 *)(s6 - 0x190) != 0 || *(s8 *)s6 != 0) {
            sp10 = fp;
            s3 = sp18;
            sp14 = spC * 8;
            j = 0;
            do {
                if (*sp10 & (1 << j)) {
                    s2 = *(u8 **)(D_003876A0 + 0xB4) + s3;
                    proceed = 0;
                    if ((s2[5] & 2) == 0) {
                        proceed = 1;
                    } else if (func_002127C0(arg0) != 0) {
                        proceed = 1;
                    }
                    if (proceed) {
                        s0 = s2[4];
                        if (s0 == 0) {
                            s0 = 1;
                        }
                        t0v = *(s16 *)s2;
                        s1 = *(s16 *)(s2 + 2) - t0v;
                        s1 = s1 * BtlChar_FrameMod(s0);
                        s0 = s0 - 1;
                        quot = (s0 != 0) ? s1 / s0 : 0;
                        s5 = sp14 + j;
                        func_00297FE0(2, s5, sp[0], sp4, t0v + quot);
                    }
                }
                j += 1;
                s3 += 6;
            } while (j < 8);
        }
        s6 += 1;
        fp += 1;
        spC += 1;
        sp18 += 0x30;
    } while ((u32)spC < 4U);
}
