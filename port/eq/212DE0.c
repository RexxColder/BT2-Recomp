#include "common.h"

/* truncates toward zero: what cvt.w.s does under the default FCSR mode */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(out, x) do { \
    (out) = (s32)(x); \
} while (0)

s32 BtlChar_GetPos(s32 arg0, s32 arg1);
void func_00212C40(s32 arg0, s32 arg1, s32 arg2);
u8 *func_00212D98(s32 arg0);
s32 BtlChar_FrameMod(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00267550(s32 arg0, s32 arg1, s32 arg2);
void func_00101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
u8 *BtlMember_GetActiveGauge(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00212DE0(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s4;
    s32 s6;
    s32 k;
    s32 cnt;
    s32 a;
    s32 v;
    s32 flag;
    u8 *p5;
    u8 *g;
    f32 f0;
    f32 f1;
    f32 t;

    for (k = 0; k < 40; k++) {
        cnt = *(s32 *)(arg0 + 0x10C4 + k * 4);
        if (cnt > 0) {
            *(s32 *)(arg0 + 0x10C4 + k * 4) = cnt - 1;
        }
    }

    s0 = *(s32 *)(arg0 + 0x368);
    if (s0 == -1) {
        return;
    }
    s6 = s0 * 4;
    func_00212C40(BtlChar_GetPos(arg0, -1), (s32)&sp0, (s32)&sp4);
    if (*(s32 *)(arg0 + 4 + s6 + 0x10C0) > 0) {
        return;
    }

    p5 = func_00212D98(s0);
    if (p5[1] < 2) {
        s4 = p5[0];
    } else {
        a = p5[1] - 1;
        v = BtlChar_FrameMod(a);
        s4 = p5[0] + v;
        if (s4 >= *(s32 *)(arg0 + 4 + s6 + 0x1020)) {
            s4 += 1;
        }
    }

    if (s0 < 0xF) {
        func_00297FE0(*(s32 *)(arg0 + 0x1534) + 3, s4, sp0, sp4, 0);
        if (func_00211310(arg0, 2, 0x600000) == 0) {
            func_00267550(*(s32 *)(arg0 + 0x1530), 6, 0);
        }
    } else {
        s2 = *(s32 *)(*(s32 *)(arg0 + 0x1530) + 4);
        f0 = ((f32)sp4 * 0.015625f - 1.0f) * 15.0f;
        f1 = ((f32)sp0 / 127.0f - 1.0f) * 200.0f;
        CVT_W_S(s1, f0);
        if (s1 >= 16) {
            s1 = 15;
        }
        if (s1 < -15) {
            s1 = -15;
        }
        CVT_W_S(s0, f1);
        a = (0 < s0);
        if (s0 > 0) {
            s0 = 0;
        }
        if (s0 < -0x3C0) {
            s0 = -0x3C0;
        }
        g = BtlMember_GetActiveGauge(arg0, a, -15, -0x3C0);
        flag = (g[0x2C] == 0) ? s2 : 0x16;
        func_00101608(*(s32 *)(arg0 + 0x1534), flag, s4, s0, s1);
        if (func_00211310(arg0, 2, 0x600000) == 0) {
            func_00267550(*(s32 *)(arg0 + 0x1530), 2, s4);
        }
    }

    *(s32 *)(arg0 + 4 + s6 + 0x1020) = s4;
    t = *(f32 *)(p5 + 4) * 30.0f;
    CVT_W_S(*(s32 *)(arg0 + 4 + s6 + 0x10C0), t);
}
