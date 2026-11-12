#include "common.h"

extern u8 *gBtlCamView;

s32 sceVu0UnitMatrix();
f32 func_003B5940(f32 x);

void sceVu0RotMatrixZ(void *dst, void *src, f32 rz);
s32 sceVu0InversMatrix();
s32 sceVu0MulMatrix();
s32 sceVu0ApplyMatrix();
s32 func_312638();
s32 sceVu0RotTransPers();
s32 func_003B5910();
s32 func_003B6608();

/* int to float with the compiler's unsigned fix-up for a negative 64-bit register (bltz) */
static f32 itof(s32 x) {
    if (x < 0) {
        s32 h = (x & 1) | (s32)((u32)x >> 1);
        f32 f = (f32)h;
        return f + f;
    }
    return (f32)x;
}

/* 0x003B5A00: builds the 4 corners (+-w, +-h) * scale of a quad (scale = a-int * 2^-12 * 2^-4), rotates them by Z
 * (angle func_003B5940(ang)) and the inverse camera view, transforms with func_312638(.., a0), projects each with
 * sceVu0RotTransPers(cam+0x100), rejects (returns the non-zero func_003B5910 result) if any corner fails, else
 * returns func_003B6608 on the 4 projected points + 4 colour/uv vectors.
 * GUESS arity: ints a0..a6, stack ints st0 (0x280), st3 (0x298), pointer st4 (0x2A0); floats f12..f19 + st1 (0x288);
 * the slot at 0x290 is not read. */
s32 func_003B5A00(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 w, s32 h,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  s32 st0, f32 ang, s32 st2, s32 st3, u8 *st4) {
    f32 m[16] __attribute__((aligned(16)));
    f32 inv[16] __attribute__((aligned(16)));
    f32 v0[4] __attribute__((aligned(16)));
    f32 v1[4] __attribute__((aligned(16)));
    f32 v2[4] __attribute__((aligned(16)));
    f32 v3[4] __attribute__((aligned(16)));
    s32 p0[4] __attribute__((aligned(16)));
    s32 p1[4] __attribute__((aligned(16)));
    s32 p2[4] __attribute__((aligned(16)));
    s32 p3[4] __attribute__((aligned(16)));
    s32 q0[4] __attribute__((aligned(16)));
    s32 q1[4] __attribute__((aligned(16)));
    s32 q2[4] __attribute__((aligned(16)));
    s32 q3[4] __attribute__((aligned(16)));
    f32 c0[4] __attribute__((aligned(16)));
    f32 c1[4] __attribute__((aligned(16)));
    f32 c2[4] __attribute__((aligned(16)));
    f32 c3[4] __attribute__((aligned(16)));
    f32 sc;
    f32 hw;
    f32 hh;
    f32 a;
    s32 r;

    sceVu0UnitMatrix(m);
    a = func_003B5940(ang);
    sceVu0RotMatrixZ(m, m, a);
    sceVu0InversMatrix(inv, gBtlCamView);
    ((s32 *)inv)[12] = 0;
    ((s32 *)inv)[13] = 0;
    ((s32 *)inv)[14] = 0;

    sc = itof(st0) * 0x1p-12f * 0x1p-4f;
    hw = itof(w) * sc;
    hh = itof(h) * sc;
    v0[0] = -hw;
    v0[1] = -hh;
    v0[2] = 0.0f;
    v0[3] = 1.0f;
    v1[0] = hw;
    v1[1] = -hh;
    v1[2] = 0.0f;
    v1[3] = 1.0f;
    v2[0] = -hw;
    v2[1] = hh;
    v2[2] = 0.0f;
    v2[3] = 1.0f;
    v3[0] = hw;
    v3[1] = hh;
    v3[2] = 0.0f;
    v3[3] = 1.0f;

    sceVu0MulMatrix(m, inv, m);
    sceVu0ApplyMatrix(v0, m, v0);
    sceVu0ApplyMatrix(v1, m, v1);
    sceVu0ApplyMatrix(v2, m, v2);
    sceVu0ApplyMatrix(v3, m, v3);
    func_312638(v0, v0, a0);
    func_312638(v1, v1, a0);
    func_312638(v2, v2, a0);
    func_312638(v3, v3, a0);
    sceVu0RotTransPers(p0, gBtlCamView + 0x100, v0, 1);
    sceVu0RotTransPers(p1, gBtlCamView + 0x100, v1, 1);
    sceVu0RotTransPers(p2, gBtlCamView + 0x100, v2, 1);
    sceVu0RotTransPers(p3, gBtlCamView + 0x100, v3, 1);

    r = func_003B5910(p0[0], p0[1], p0[2]);
    if (r != 0) {
        return r;
    }
    r = func_003B5910(p1[0], p1[1], p1[2]);
    if (r != 0) {
        return r;
    }
    r = func_003B5910(p2[0], p2[1], p2[2]);
    if (r != 0) {
        return r;
    }
    r = func_003B5910(p3[0], p3[1], p3[2]);
    if (r != 0) {
        return r;
    }

    q0[0] = p0[0];
    q0[1] = p0[1];
    q0[2] = p0[2];
    q0[3] = 0;
    q1[0] = p1[0];
    q1[1] = p1[1];
    q1[2] = p1[2];
    q1[3] = 0;
    q2[0] = p2[0];
    q2[1] = p2[1];
    q2[2] = p2[2];
    q2[3] = 0;
    q3[0] = p3[0];
    q3[1] = p3[1];
    q3[2] = p3[2];
    q3[3] = 0;
    c0[0] = f12;
    c0[1] = f13;
    c0[2] = 1.0f;
    c0[3] = 1.0f;
    c1[0] = f14;
    c1[1] = f15;
    c1[2] = 1.0f;
    c1[3] = 1.0f;
    c2[0] = f16;
    c2[1] = f17;
    c2[2] = 1.0f;
    c2[3] = 1.0f;
    c3[0] = f18;
    c3[1] = f19;
    c3[2] = 1.0f;
    c3[3] = 1.0f;
    return func_003B6608(q0, q1, q2, q3, a1, a2, a3, a4, c0, c1, c2, c3,
                         *(s64 *)(st4 + 0x30), 1, st3);
}
