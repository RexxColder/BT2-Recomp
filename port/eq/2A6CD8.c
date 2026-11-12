#include "common.h"

s32 Gsc_GetInt(s32 arg0);
f32 Gsc_GetFloat(void);
s32 Gsc_ResetOperands(void);
s32 func_002A0010(s32 arg0);
void *func_002A3DB8(s32 arg0);
void *func_002A4E38(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                    s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10);

s32 func_002A6CD8(s32 arg0, u8 *arg1) {
    s32 s2 = 0;
    s32 var_s0;
    s32 sp20;
    u8 *bp;
    u8 *s0p;
    f32 m;
    s32 k, v, old;

    if (arg0 == 0) {
        var_s0 = 0xE;
        if (func_002A0010(0x70) != 0) {
            var_s0 = Gsc_GetInt(0x57);
        }
        sp20 = 0;
        if (func_002A0010(0x57) != 0) {
            sp20 = 0xFFFFFF;
        }
        bp = (u8 *)&sp20;
        Gsc_ResetOperands();
        s0p = (u8 *)func_002A4E38(0x20, (s8)var_s0, 0, 0, 0x200, 0x1C0,
                                  bp[0], bp[1], bp[2], bp[3], 0);
        m = Gsc_GetFloat() * 300.0f;
        *(s32 *)(s0p + 0x20) = 1;
        k = (s32)m;
        if (m - (f32)k > 0.5f || (m - (f32)k == 0.5f && (k & 1))) {
            k++;
        } else if (m - (f32)k < -0.5f || (m - (f32)k == -0.5f && (k & 1))) {
            k--;
        }
        *(s16 *)(s0p + 0x24) = (s16)k;
        *(s32 *)arg1 = 0;
        v = func_002A0010(0x77);
        arg1[4] = (u8)v;
        if (v == 0) {
            s2 = 1;
        }
        return s2;
    } else if (arg0 == 1) {
        if (arg1[4] != 0) {
            s0p = (u8 *)func_002A3DB8(0x20);
            *(s8 *)(s0p + 0x18) = 0;
        }
        return 0;
    } else if (arg0 == 2) {
        s0p = (u8 *)func_002A3DB8(0x20);
        if (*(s32 *)(s0p + 0x20) != 0) {
            return 0;
        }
        old = *(s32 *)arg1;
        s2 = (0 < old);
        *(s32 *)arg1 = old + 1;
        return s2;
    }
    return 0;
}
