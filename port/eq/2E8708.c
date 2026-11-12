#include "common.h"

/* 0x002E8708: leaf. Reads fields of the record arg0 (u8 at +7, +8, +9; u16 at +0x2A; s32 at +0xC)
 * and stores the results through eleven pointer arguments (arg1 is not used). The selector byte
 * at +8 (1, 0, 2..3, or 4+) decides one 16-bit output (arg10); the rest is fixed: 0x10, 2, 1,
 * half of the +0xC word, and 0xFF. Returns 0. */
s32 func_002E8708(u8 *arg0, s32 arg1, s16 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, u8 *arg6,
                  s32 *arg7, s32 *arg8, s32 *arg9, s16 *arg10) {
    s32 k = *(u8 *)(arg0 + 0x8);

    *arg2 = (s16)(*(u8 *)(arg0 + 0x7) << 4);
    *arg6 = (u8)((*(u8 *)(arg0 + 0x9) & 3) + 1);
    *arg7 = *(u16 *)(arg0 + 0x2A);

    if (k == 1) {
        *arg10 = 1;
    } else if (k == 0) {
        *arg10 = 0;
    } else if (k == 2 || k == 3) {
        *arg10 = 2;
    }

    *arg4 = 0x10;
    *arg5 = 2;
    *arg9 = 1;
    *arg8 = *(s32 *)(arg0 + 0xC) / 2;
    *arg3 = 0xFF;
    return 0;
}
