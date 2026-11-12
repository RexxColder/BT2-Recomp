#include "common.h"

f32 atan2f(f32 farg0, f32 farg1);
f32 sinf(f32 farg0);
s32 func_002B1DD0(s32 arg0);
f32 func_0029DFD0(s32 arg0);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
extern f32 D_00387660;
extern f32 D_00387664;
extern f32 D_00387668;
extern f32 D_0038766C;
extern f32 D_00387670;

f32 func_002B2230(s32 arg0, s32 *arg1, s32 *arg2) {
    u8 sp[0x30];
    f32 f20;
    f32 f4;
    f32 ang;
    f32 t;
    f32 ret;
    s32 s0;
    s32 n;

    func_003126C8((s32)(sp + 0x10), func_002B1DD0(0) + 0x50);
    func_003126C8((s32)(sp + 0x20), func_002B1DD0(0) + 0x60);
    func_00312650((s32)sp, arg0, (s32)(sp + 0x10));
    f20 = func_0029DFD0((s32)sp);
    ang = atan2f(*(f32 *)sp, *(f32 *)(sp + 8)) - *(f32 *)(sp + 0x24);
    f20 = (f20 - 200.0f) / D_00387660;
    f4 = 1.0f - f20;
    if (ang < D_00387664) {
        ang += D_00387668;
    }
    if (D_0038766C < ang) {
        ang -= D_00387670;
    }
    /* first output: cvt.w.s (truncates toward zero) of f4 * 127, clamped to 0..127 */
    t = f4 * 127.0f;
    n = (s32)t;
    s0 = n;
    if (s0 < 0) {
        s0 = 0;
    }
    if (s0 >= 0x80) {
        s0 = 0x7F;
    }
    ret = sinf(ang);
    *arg1 = s0;
    ret = (ret * 64.0f) + 64.0f;
    /* second output: cvt.w.s (truncates toward zero) of the return value, clamped */
    t = ret;
    n = (s32)t;
    if (n < 0) {
        n = 0;
    }
    if (n >= 0x80) {
        n = 0x7F;
    }
    *arg2 = n;
    return ret;
}
