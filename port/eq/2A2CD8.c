#include "common.h"

extern s32 D_00387E00;

s64 func_002A2C98(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x002A2CD8: GS packet builder. Writes six 64-bit words at arg1 (a sub-packet for a quad or a
 * sprite): the word returned by func_002A2C98(D_00387E00, arg6, arg7+0x40, arg7), the constant
 * 0x3F800000:80808080, a zero, two words with the 16-bit-shifted coordinates (arg2+0x700 and
 * arg3+0x720 times 16, with arg4 and arg5 times 16 in the last word) and the fixed 0x0FFFFFFF
 * high field. Returns arg1 + 0x30 when written, else arg1 (when a coordinate is out of range:
 * the scaled y must be <= 0xFFFF, the scaled counts must be positive). */
s64 *func_002A2CD8(s32 arg0, s64 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s64 *s2 = arg1;
    s64 s6 = (s32)((arg2 + 0x700) << 4);
    s64 s5 = (s32)((arg2 + arg4 + 0x700) << 4);
    s64 s3 = (s32)((arg3 + 0x720) << 4);
    s64 s4 = (s32)((arg3 + arg5 + 0x720) << 4);
    s64 s1 = (s32)(arg4 << 4);
    s64 s0 = (s32)(arg5 << 4);

    if (s6 <= 0) {
        return s2;
    }
    if (s5 > 0xFFFF) {
        return s2;
    }
    if (s3 <= 0) {
        return s2;
    }
    if (s4 > 0xFFFF) {
        return s2;
    }

    s2[0] = (s64)func_002A2C98(D_00387E00, arg6, arg7 + 0x40, arg7);
    s2[1] = (s64)0x3F80000080808080;
    s2[2] = 0;
    s2[3] = (s6 | (s3 << 16)) | (s64)0x0FFFFFFF00000000;
    s2[4] = s1 | (s0 << 16);
    s2[5] = (s5 | (s4 << 16)) | (s64)0x0FFFFFFF00000000;
    return s2 + 6;
}
