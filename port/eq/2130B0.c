#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
void func_00212C40(s32 arg0, s32 arg1, s32 arg2);
s32 func_0025FBE8(s32 arg0, s64 arg1, s32 arg2, s32 arg3);
void func_00101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00267550(s32 arg0, s32 arg1, s32 arg2);
s32 func_00241B58(s32 arg0, s32 arg1);
s32 func_00210D98(s32 arg0);

void func_002130B0(u8 *arg0) {
    s32 sp[2];
    s32 s0;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 flags;
    s32 pos;
    s32 a2f;
    s32 ix;
    s32 iy;
    f32 xa;
    f32 ya;

    s4 = 0;
    flags = func_001FA3A8(BtlObjXf_Update((s32)arg0));

    s3 = (flags & 0x20000000) ? 0x53 : -1;
    if (flags & 0x40000000) {
        s3 = 0x55;
        s4 = 1;
    }
    if (flags & 0x04000000) {
        s3 = 0x57;
        s4 = 2;
    }
    if (flags & 0x08000000) {
        s3 = 0x59;
        s4 = 3;
    }
    if (flags & 0x10000000) {
        s3 = 0x5B;
        s4 = 4;
    }
    if (s3 < 0) {
        return;
    }

    pos = BtlChar_GetPos((s32)arg0);
    func_00212C40(pos, (s32)sp, (s32)(sp + 1));

    xa = (((f32)sp[0] / 127.0f) - 1.0f) * 200.0f;
    ya = (((f32)sp[1] * 0.015625f) - 1.0f) * 15.0f;

    /* cvt.w.s: truncates toward zero */
    iy = (s32)ya;
    ix = (s32)xa;

    s1 = iy;
    s0 = ix;
    if (s1 >= 0x10) {
        s1 = 0xF;
    }
    a2f = (0 < s0) ? 1 : 0;
    if (s1 < -0xF) {
        s1 = -0xF;
    }
    if (a2f != 0) {
        s0 = 0;
    }
    if (s0 < -0x3C0) {
        s0 = -0x3C0;
    }

    if (func_0025FBE8(W(arg0, 0x1530), (s64)0x8000, a2f, -0xF) != 0) {
        func_00101608(W(arg0, 0x1534), W(W(arg0, 0x1530), 4), s3, s0, s1);
        if (func_00211310((s32)arg0, 2, 0x600000) == 0) {
            func_00267550(W(arg0, 0x1530), 2, s3);
        }
    }

    if (((s32 (*)(s32, s64))func_0025FBE8)(W(arg0, 0x1530), (s64)0x8000 << 24) != 0) {
        s5 = 1;
        if (s4 < 5) {
            if (s4 >= 2) {
                if (func_00241B58((s32)arg0, s4) > 0) {
                    s5 = ((func_00210D98((s32)arg0) & 0x80) == 0) ? 1 : 0;
                }
            }
        }
        s3 = s3 + 1;
        if (s5 != 0) {
            func_00101608(W(arg0, 0x1534), W(W(arg0, 0x1530), 4), s3, s0, s1);
            if (func_00211310((s32)arg0, 2, 0x600000) == 0) {
                func_00267550(W(arg0, 0x1530), 2, s3);
            }
        }
    }
}
