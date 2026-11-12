#include "common.h"

void func_002E3240(s32 arg0, s32 arg1, s32 arg2);

s32 func_002E3028(s32 arg0, s32 arg1) {
    u8 *ctx;
    u8 *cur;
    u8 *s2;
    u32 t0;
    u32 a3;
    u32 v1;
    s32 s1;
    s32 a2;
    s32 tv;
    s32 cond;

    ctx = (u8 *)arg0 + 0x160;
    *(s32 *)(ctx + 0x434) = *(s32 *)(ctx + 0x434) + 1;
    cond = ((*(s32 *)(ctx + 0x308) != 0) && (*(s32 *)(ctx + 0x308) != 0x20))
        || (*(s32 *)(ctx + 0x30C) != 0);
    if (cond) {
        *(s32 *)(ctx + 0x494) = *(s32 *)(ctx + 0x494) + 1;
    }

    s2 = (u8 *)arg1;
    cur = (u8 *)(arg1 & ~3);
    s1 = (arg1 & 3) * 8;

    /* 8 bytes: t0 = bytes 0..3 (byte 0 signed), a3 = bytes 4..7 (byte 4 signed) */
    t0 = ((u32)(s32)(s8)cur[0] << 24) | ((u32)cur[1] << 16) | ((u32)cur[2] << 8) | (u32)cur[3];
    a3 = ((u32)(s32)(s8)cur[4] << 24) | ((u32)cur[5] << 16) | ((u32)cur[6] << 8) | (u32)cur[7];
    cur += 8;
    if (s1 != 0) {
        *(s32 *)(ctx + 0x30) = (s32)((t0 << s1) | (a3 >> (32 - s1)));
        t0 = a3 << s1;
    } else {
        *(s32 *)(ctx + 0x30) = (s32)t0;
        t0 = a3;
    }

    /* 4 more bytes (byte 0 signed) into a3 */
    a3 = ((u32)(s32)(s8)cur[0] << 24) | ((u32)cur[1] << 16) | ((u32)cur[2] << 8) | (u32)cur[3];
    cur += 4;

    a2 = 0;
    for (;;) {
        if (a2 > 0xFFFFF) {
            break;
        }
        v1 = t0 >> 8;
        if (s1 >= 9) {
            v1 |= a3 >> (40 - s1);
        }
        t0 <<= 8;
        if (v1 == 1) {
            break;
        }
        s1 += 8;
        a2 += 1;
        if (s1 >= 0x20) {
            s1 -= 0x20;
            t0 = a3 << s1;
            a3 = ((u32)(s32)(s8)cur[0] << 24) | ((u32)cur[1] << 16) | ((u32)cur[2] << 8) | (u32)cur[3];
            cur += 4;
        }
    }

    func_002E3240(arg0, arg1, a2 + 4);
    tv = s1 + ((s32)(cur - s2) * 8);
    {
        s32 t1v = tv - 0x39;
        if (t1v < 0) {
            t1v = tv - 0x32;
        }
        return arg1 + (t1v >> 3);
    }
}
