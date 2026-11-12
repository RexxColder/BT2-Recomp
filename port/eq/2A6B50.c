#include "common.h"

f32 Gsc_GetFloat(void);
s8 Gsc_GetInt(s32 arg0);
void Gsc_ResetOperands(void);
u8 func_002A0010(s32 arg0);
s32 func_002A3DB8(s32 arg0);
s32 func_002A4E38(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10);

s32 func_002A6B50(s32 arg0, void *arg1) {
    u8 *p;
    s32 s0;
    s32 s2;
    s32 sp20;
    s32 ptr;
    s32 t;
    f32 fr;
    u8 v8;

    p = (u8 *)arg1;
    s2 = 0;
    if (arg0 == 1) {
        if (p[4] != 0) {
            ptr = func_002A3DB8(0x1F);
            *(u8 *)(ptr + 0x18) = 0;
        }
        return s2;
    }
    if (arg0 == 0) {
        s0 = 0xE;
        if (func_002A0010(0x70) != 0) {
            s0 = Gsc_GetInt(0x57);
        }
        sp20 = 0;
        if (func_002A0010(0x57) != 0) {
            sp20 = 0xFFFFFF;
        }
        Gsc_ResetOperands();
        ptr = func_002A4E38(0x1F, (s8)s0, 0, 0, 0x200, 0x1C0, sp20 & 0xFF, (sp20 >> 8) & 0xFF,
                            (sp20 >> 16) & 0xFF, (sp20 >> 24) & 0xFF, 0);
        fr = Gsc_GetFloat();
        *(s32 *)(ptr + 0x20) = 2;
        fr = fr * 300.0f;
        /* cvt.w.s: truncates toward zero */
        t = (s32)fr;
        *(s16 *)(ptr + 0x24) = (s16)t;
        *(s32 *)p = 0;
        v8 = func_002A0010(0x77);
        p[4] = v8;
        if (v8 == 0) {
            s2 = 1;
        }
        return s2;
    }
    if (arg0 == 2) {
        ptr = func_002A3DB8(0x1F);
        if (*(s32 *)(ptr + 0x20) == 0) {
            t = *(s32 *)p;
            s2 = (t > 0);
            *(s32 *)p = t + 1;
        }
        return s2;
    }
    return 0;
}
