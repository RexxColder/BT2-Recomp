#include "common.h"

s32 func_002A3DB8(s32 arg0);

#define SH(off, v) (*(u16 *)(rec + (off)) = (u16)(v))
#define SB(off, v) (*(u8 *)(rec + (off)) = (u8)(v))
#define SW(off, v) (*(s32 *)(rec + (off)) = (s32)(v))

/* 0x002A4CF0: fills the 40-byte entry of table D_003B1FF0 at index arg0 (func_002A3DB8) from 17 arguments:
 * arg1 low byte (+0x19), arg2 (+0x1C, and +0x14 = arg2 != 0), arg3 low byte (+0x1A), arg4..arg7 halfwords
 * (+0..+6), arg8..arg11 bytes (+8..+0xB), and arg12..arg15 halfwords at +0xC..+0x12 in an order chosen by
 * arg16 (1, 2, other). The entry flag +0x18 = 1, +0x20 = 0, +0x24 and +0x26 = 0. */
void func_002A4CF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                   s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16) {
    u8 *rec;

    rec = (u8 *)(s32)func_002A3DB8(arg0);
    SB(0x18, 1);
    SB(0x19, arg1);
    SH(0x0, arg4);
    SH(0x2, arg5);
    SH(0x4, arg6);
    SH(0x6, arg7);
    SB(0x8, arg8);
    SB(0x9, arg9);
    SB(0xA, arg10);
    SB(0xB, arg11);
    SB(0x1A, arg3);
    SW(0x14, 0);
    SW(0x20, 0);
    SH(0x24, 0);
    SH(0x26, 0);
    SW(0x1C, arg2);

    if (arg16 == 1) {
        SH(0xC, arg14);
        SH(0xE, arg13);
        SH(0x10, arg12);
        SH(0x12, arg15);
    } else if (arg16 == 2) {
        SH(0xC, arg12);
        SH(0xE, arg15);
        SH(0x10, arg14);
        SH(0x12, arg13);
    } else {
        SH(0xC, arg12);
        SH(0xE, arg13);
        SH(0x10, arg14);
        SH(0x12, arg15);
    }

    if (arg2 != 0) {
        SW(0x14, 1);
    }
}
