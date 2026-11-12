#include "common.h"

u8 *func_00126040(void *arg0);
s32 BtlChar_GetPos(void *arg0);
f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
f32 func_0029DFD0(void *arg0);
void func_00312650(void *arg0, s32 arg1, s32 arg2);
void func_00312680(f32 farg0, void *arg1, void *arg2);
extern f32 D_003840A0;

void func_00121050(u8 *arg0, s32 arg1, f32 farg0, f32 farg1) {
    u8 sp[0x10];
    u8 *v0;
    s32 pos;
    f32 dist;
    f32 ang;
    f32 c1;
    f32 s1f;
    f32 s2f;
    f32 c2;
    f32 f21;
    f32 f23;
    f32 fA;
    f32 fB;
    f32 t0f;
    f32 t1f;
    s32 q;

    v0 = func_00126040(arg0);
    pos = BtlChar_GetPos(v0);
    func_00312650(sp, arg1, pos);
    *(s32 *)(sp + 4) = 0;
    dist = func_0029DFD0(sp);
    if (dist < farg0) {
        return;
    }

    func_00312680(1.0f / dist, sp, sp);
    v0 = func_00126040(arg0);
    ang = *(f32 *)(v0 + 0x150);
    c1 = cosf(ang);
    f21 = c1 * *(f32 *)(sp + 0);
    s1f = sinf(ang);
    f23 = f21 - (s1f * *(f32 *)(sp + 8));
    s2f = sinf(ang);
    f21 = s2f * *(f32 *)(sp + 0);
    c2 = cosf(ang);
    f21 = f21 + (c2 * *(f32 *)(sp + 8));

    fA = (f32)arg0[0x24] * D_003840A0;
    fA = fA + fA;
    fA = fA - 1.0f;
    fB = (f32)arg0[0x25] * D_003840A0;
    fB = fB + fB;
    fB = fB - 1.0f;

    t0f = f23 - fA;
    t1f = (-f21) - fB;
    t0f = t0f * farg1;
    t1f = t1f * farg1;
    f23 = fA + t0f;
    t1f = fB + t1f;
    t0f = ((f23 * 0.5f) + 0.5f) * 255.0f;
    t1f = ((t1f * 0.5f) + 0.5f) * 255.0f;

    /* cvt.w.s truncates toward zero (saturating); then clamp to 0..255 */
    q = (s32)t0f;
    if (q < 0) {
        q = 0;
    }
    if (q >= 0x100) {
        q = 0xFF;
    }
    arg0[0x10] = (u8)q;

    q = (s32)t1f;
    if (q < 0) {
        q = 0;
    }
    if (q >= 0x100) {
        q = 0xFF;
    }
    arg0[0x11] = (u8)q;
}
