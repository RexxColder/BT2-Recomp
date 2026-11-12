#include "common.h"

extern s32 D_0037A290[];

s32 func_002DC830(s32 arg0, s32 *arg1);
s32 func_002C2FF0(u8 *arg0, s32 arg1);
void func_002C49E8(u8 *arg0, s32 arg1);
s32 func_002C3EB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

s32 func_002C3D40(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    s32 sp[0x20];
    u8 *s1;
    s32 s0;
    s32 s6;
    s32 w;
    s32 r;
    s32 a3v;
    s32 t;
    s32 (*fp)(s32, s32, s32, s32);

    s6 = 0;
    *arg3 = 0;
    *arg4 = 0;
    s1 = (u8 *)*(s32 *)(arg0 + 0x1F7C);

    if (func_002DC830(*(s32 *)s1, sp) != 0) {
        s6 = func_002C2FF0(arg0, 0xFF000D06);
    }

    s0 = sp[9];
    a3v = sp[4];
    if (s0 < 0) {
        return func_002C2FF0(arg0, 0xFF000D0E);
    }
    if (s0 == 0) {
        *arg4 = 1;
        return 0;
    }
    if (arg2 < s0) {
        func_002C49E8(arg0, 0);
        return 0;
    }

    w = *(s32 *)(s1 + a3v * 4 - 0x2B0);
    if (w != 0) {
        r = func_002C3EB8(w, *(s32 *)(s1 + 0x150), *(s32 *)(s1 + 0x154), a3v, arg1, s0);
        *arg4 = r;
    } else {
        fp = (s32 (*)(s32, s32, s32, s32))D_0037A290[sp[5]];
        r = fp((s32)arg0, sp[6], arg1, s0);
        *arg4 = r;
    }

    t = *arg4;
    if (t != 0) {
        if (t != 1) {
            s6 = t;
        } else {
            *arg3 = s0;
        }
    }
    return s6;
}
