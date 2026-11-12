#include "common.h"

/* 0x002E9688: parses a 16-byte big-endian header at arg0 (count arg1 must be >= 0x10): returns -1 when arg1 < 0x10,
 * -2 when the first halfword is not 0x8000, else stores the halfword (BE +2) + 4 at arg2, byte +4 at arg3, byte +6
 * at arg4, byte +5 at arg5, byte +7 at arg6, BE word +8 at arg7, BE word +0xC at arg8, and: if the byte at arg4 is 0,
 * arg9 = 0; otherwise arg9 = ((s8)arg5 * 8 - 16) / (s8)arg4. Returns 0 on success. */
s32 func_002E9688(u8 *arg0, s32 arg1, u16 *arg2, u8 *arg3, s8 *arg4, s8 *arg5, u8 *arg6, s32 *arg7, s32 *arg8,
                  s32 *arg9) {
    u8 *p = arg0;

    if (arg1 < 0x10) {
        return -1;
    }
    if ((((u32)p[0] << 8) | p[1]) != 0x8000) {
        return -2;
    }
    *arg2 = (u16)((((u32)p[2] << 8) | p[3]) + 4);
    *arg3 = p[4];
    *arg5 = (s8)p[5];
    *arg4 = (s8)p[6];
    *arg6 = p[7];
    *arg7 = (s32)(((u32)p[8] << 24) | ((u32)p[9] << 16) | ((u32)p[10] << 8) | p[11]);
    *arg8 = (s32)(((u32)p[12] << 24) | ((u32)p[13] << 16) | ((u32)p[14] << 8) | p[15]);
    if (*arg4 == 0) {
        *arg9 = 0;
        return 0;
    }
    *arg9 = ((((s32)*arg5) << 3) - 16) / (s32)*arg4;
    return 0;
}
