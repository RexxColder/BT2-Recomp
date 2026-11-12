#include "common.h"

s32 func_002C4850(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002DC538(s32 arg0);
s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002DA888(s32 arg0, s32 arg1, s32 arg2);
void func_002DA8D8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002DA928(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002C4FB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002C1180(s32 arg0);
void func_002C4838(s32 arg0);
s32 func_002C11A0(s32 arg0);
void func_002C3B98(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3);
void func_002C49E8(s32 arg0, s32 arg1);
s32 func_002C3D40(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4);
void func_002C3B20(s32 arg0, s32 arg1, s64 arg2);

/* 0x002C3840 (per-frame work of an animation/sound channel). out1 and out2 receive the remaining counts; the record
 * at obj+0x1F7C holds a state word at +0x158 and the channel list at (*obj+0x1F7C). Returns the status word of the
 * checks (ret) or a count on the early exits, as the paths in the asm. */
s32 func_002C3840(u8 *obj, s32 arg1, s32 arg2, s32 *out1, s32 *out2, s32 arg5) {
    u8 *s4;
    u8 *s3;
    s32 ret = 0;
    s32 fp;
    s32 s0;
    s32 w0 = 0;
    s32 w4 = 0;
    s32 w8 = 0;
    s32 wc = 0;
    s32 w10 = 0;
    s32 a1v;
    s32 v1;
    s32 a0v;
    s32 a2v;
    s32 v;

    *out1 = 0;
    *out2 = 0;
    s4 = *(u8 **)(obj + 0x1F7C);
    s3 = *(u8 **)s4;

    if (func_002C4850((s32)obj, arg1, arg2, arg5) == 0) {
        return 0;
    }

    fp = 0;
    if (arg2 >= 4) {
        fp = func_002DC538(arg1);
    }
    func_002D07B0((s32)obj, 0x57);
    s0 = func_002D07B0((s32)obj, 0x58);
    func_002DA888((s32)s3, s0, s0);
    if (func_002D07B0((s32)obj, 0x5B) != 0) {
        func_002DA8D8((s32)s3, (s32)func_002C3B20, (s32)obj);
    } else {
        func_002DA8D8((s32)s3, 0, 0);
    }

    if (func_002DA928((s32)s3, arg1, arg2, (s32)&w0, (s32)&w4) != 0) {
        ret = func_002C2FF0((s32)obj, 0xFF000D03);
    }

    s0 = w4;
    if ((s0 & 0x20000) != 0) {
        func_002C4FB8((s32)obj, (s32)s3, arg1, arg2);
        s0 = w4;
    }

    if (s0 == 0x80000) {
        if (func_002C1180((s32)obj) != 0) {
            func_002C4838((s32)obj);
            *out1 = 0x800;
            *(s32 *)(s4 + 0x158) = 0x800;
            return ret;
        }
        if (func_002C11A0((s32)obj) != 0) {
            *out1 = 0x800;
            *(s32 *)(s4 + 0x158) = 0x800;
            return ret;
        }
    }

    if (fp != 0) {
        if ((w4 & 0x40000) != 0) {
            ret = func_002C3D40(obj, arg1 + w0, arg2 - w0, &wc, &w10);
            if (w10 != 1) {
                *(s32 *)(s4 + 0x158) = w10;
                return ret;
            }
            *out1 = w0 + wc;
            *(s32 *)(s4 + 0x158) = -1;
            return ret;
        }

        func_002C49E8((s32)obj, (s32)&w8);
        if (w8 != 0) {
            return w8;
        }
        if (*(s32 *)(obj + 0x28) < arg2) {
            v = (w0 <= 0) ? 1 : w0;
            *out1 = v;
            *out2 = v;
            return ret;
        }
        return 0;
    }

    func_002C3B98(obj, arg1, arg2, out2);
    *out1 = *out2;
    a1v = *out2;
    if (a1v <= 0) {
        return *out2;
    }

    v1 = *(s32 *)(s4 + 0x158);
    if (v1 < 0) {
        return ret;
    }

    a0v = *(s32 *)(obj + 0x28);
    if (v1 < a0v) {
        a2v = v1 + a1v;
        if (a0v < a2v) {
            *out2 = a1v - (a0v - v1);
            *(s32 *)(s4 + 0x158) = a0v + *out2;
        } else {
            *(s32 *)(s4 + 0x158) = a2v;
            *out2 = 0;
        }
    } else {
        *(s32 *)(s4 + 0x158) = v1 + a1v;
    }
    return ret;
}
