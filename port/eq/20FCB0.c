#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
void func_0020FAD0(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 func_002127C0(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 BtlChar_FrameMod(s32 arg0);
extern u8 *D_003876A0;
extern f32 D_003859F8;

void func_0020FCB0(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 i;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 s7p;
    s32 b;
    s32 s6;
    s32 s4;
    s32 s3;
    s32 s2;
    s32 s0;
    s32 s1;
    s32 t0;
    s32 fm;
    s32 q;
    s32 tv;
    s32 bmap;
    s32 bit;
    s32 s0p;
    s32 pos;

    pos = BtlChar_GetPos(arg0);
    i = 0;
    sp14 = 0;
    func_0020FAD0(pos, (s32)&sp0, (s32)&sp4, 200.0f, D_003859F8);

    do {
        s7p = arg0 + 0x340 + i;
        if (*(u8 *)s7p != 0 || *(u8 *)(s7p + 0x190) != 0) {
            sp10 = i * 8;
            spC = i + 0x350;
            b = 0;
            s6 = sp14;
            do {
                s4 = 1 << b;
                s3 = sp10 + b;
                s2 = *(s32 *)(D_003876A0 + 0xB0) + s6;
                if ((*(u8 *)s7p & s4) != 0) {
                    if ((*(u8 *)(s2 + 5) & 2) == 0 || func_002127C0(arg0) != 0) {
                        s0 = *(u8 *)(s2 + 4);
                        s1 = *(s16 *)(s2 + 2);
                        if (s0 == 0) {
                            s0 = 1;
                        }
                        t0 = *(s16 *)(s2 + 0);
                        s1 = s1 - t0;
                        fm = BtlChar_FrameMod(s0);
                        s0 = s0 - 1;
                        s1 = s1 * fm;
                        /* divisor is s0 (adjusted - 1); the asm traps when it is 0 */
                        q = s1 / s0;
                        s1 = q;
                        tv = s3;
                        if (s3 < 0) {
                            tv = s3 + 7;
                        }
                        tv = tv >> 3;
                        bmap = *(u8 *)(D_003876A0 + tv + 0x90);
                        bit = (bmap >> ((s3 - tv * 8) & 31)) & 1;
                        t0 = *(s16 *)(s2 + 0) + s1;
                        if (bit != 0) {
                            s0p = arg0 + spC;
                            if (((*(u8 *)s0p) >> b) & 1) {
                                goto inner_end;
                            }
                            func_00297FE0(0x81, s3, sp0, sp4, t0);
                            *(u8 *)s0p = (u8)(*(u8 *)s0p | s4);
                            goto inner_end;
                        } else if ((*(u8 *)(s2 + 5) & 4) != 0) {
                            func_00297FE0(0x81, s3, sp0, sp4, t0);
                        } else {
                            func_00297FE0(1, s3, sp0, sp4, t0);
                        }
                    }
                } else {
                    s0p = arg0 + spC;
                    if (((*(u8 *)s0p) >> b) & 1) {
                        func_00297FE0(0x41, s3, 0, 0, 0);
                        *(u8 *)s0p = (u8)(*(u8 *)s0p & ~s4);
                    }
                }
inner_end:
                b += 1;
                s6 += 6;
            } while (b < 8);
        }
        i += 1;
        sp14 += 0x30;
    } while (i < 16);
}
