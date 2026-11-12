#include "common.h"
#include "vu0_state.h"

/* out[i] = c0[i]*v[0] + c1[i]*v[1] + c2[i]*v[2] + c3[i]*v[3] (one vmulax / vmadday / vmaddaz / vmaddw chain) */
static void vu0Chain(f32 out[4], f32 cols[4][4], const f32 v[4]) {
    s32 i;
    f32 acc;

    for (i = 0; i < 4; i++) {
        acc = cols[0][i] * v[0];
        acc = acc + cols[1][i] * v[1];
        acc = acc + cols[2][i] * v[2];
        out[i] = acc + cols[3][i] * v[3];
    }
}

static void vu0Load(f32 *dst, const u8 *src) {
    __builtin_memcpy(dst, src, 16);
}

static void vu0Store(u8 *dst, const f32 *src) {
    __builtin_memcpy(dst, src, 16);
}

/* 0x002625D0: VU0 matrix pipeline. ctx = output packet (0x30 int lanes, 0x50, 0x60), vtx = 8 transformed
 * vectors in and out, mat = two 4x4 matrices (vf1..vf4, vf5..vf8), pt = two points. Returns the sticky
 * status bits 0x40 / 0x80 of the range test on the perspective result. */
s32 func_002625D0(u8 *ctx, u8 *vtx, u8 *mat, u8 *pt) {
    f32 cols[4][4];
    f32 mat0[4][4];
    f32 mat1[4][4];
    f32 tA[4][4];
    f32 tB[4][4];
    f32 p[4];
    f32 q[4];
    f32 v1w[4];
    f32 bA[4];
    f32 bB[4];
    f32 b15[4];
    f32 e[4];
    f32 sv[4];
    f32 g0[4];
    f32 g1[4];
    f32 h0[4];
    f32 h1[4];
    f32 hv[4];
    f32 X[4];
    f32 Y[4];
    f32 K[4];
    f32 gc[4][4];
    f32 P[4];
    f32 Pn[4];
    f32 flagv[5];
    s32 I[4];
    f32 qd;
    f32 w20[4];
    f32 o50[4];
    f32 o60[4];
    s32 i;
    s32 status;

    for (i = 0; i < 4; i++) {
        gc[0][i] = gVu0.vf[24][i];
        gc[1][i] = gVu0.vf[25][i];
        gc[2][i] = gVu0.vf[26][i];
        gc[3][i] = gVu0.vf[27][i];
    }

    /* columns of the first stage (vf9..vf12) and the two matrices (vf1..vf4, vf5..vf8) */
    vu0Load(cols[0], vtx + 0x80);
    vu0Load(cols[1], vtx + 0x90);
    vu0Load(cols[2], vtx + 0xA0);
    vu0Load(cols[3], vtx + 0xB0);
    vu0Load(mat0[0], mat + 0x00);
    vu0Load(mat0[1], mat + 0x10);
    vu0Load(mat0[2], mat + 0x20);
    vu0Load(mat0[3], mat + 0x30);
    vu0Load(mat1[0], mat + 0x40);
    vu0Load(mat1[1], mat + 0x50);
    vu0Load(mat1[2], mat + 0x60);
    vu0Load(mat1[3], mat + 0x70);

    vu0Chain(tA[0], cols, mat0[0]);
    vu0Chain(tA[1], cols, mat0[1]);
    vu0Chain(tA[2], cols, mat0[2]);
    for (i = 0; i < 4; i++) {
        tA[3][i] = cols[3][i];
    }
    vu0Chain(tB[0], cols, mat1[0]);
    vu0Chain(tB[1], cols, mat1[1]);
    vu0Chain(tB[2], cols, mat1[2]);
    for (i = 0; i < 4; i++) {
        tB[3][i] = cols[3][i];
    }
    vu0Store(vtx + 0x00, tA[0]);
    vu0Store(vtx + 0x10, tA[1]);
    vu0Store(vtx + 0x20, tA[2]);
    vu0Store(vtx + 0x30, tA[3]);
    vu0Store(vtx + 0x40, tB[0]);
    vu0Store(vtx + 0x50, tB[1]);
    vu0Store(vtx + 0x60, tB[2]);
    vu0Store(vtx + 0x70, tB[3]);

    /* blend of the two stage results with the point p (w taken as 1.0) and the scale in vtx+0xC0 */
    vu0Load(p, ctx + 0x10);
    vu0Load(q, ctx + 0x00);
    v1w[0] = p[0];
    v1w[1] = p[1];
    v1w[2] = p[2];
    v1w[3] = 1.0f;
    vu0Chain(bA, tA, v1w);
    vu0Chain(bB, tB, v1w);

    for (i = 0; i < 4; i++) {
        e[i] = (bA[i] - bB[i]) * q[3];
    }
    for (i = 0; i < 3; i++) {
        e[i] = bB[i] + e[i];
    }
    vu0Load(sv, vtx + 0xC0);
    for (i = 0; i < 3; i++) {
        e[i] = e[i] * sv[3];
        e[i] = e[i] + sv[3];
    }
    b15[0] = 0.0f + e[0];
    b15[1] = 0.0f;
    b15[2] = 1.0f;
    b15[3] = bB[3];

    /* second blend: the two points g0, g1 through the first matrices, then through the view (vf24..vf27) */
    vu0Load(g0, pt + 0x00);
    vu0Load(g1, pt + 0x10);
    for (i = 0; i < 4; i++) {
        h0[i] = q[i] - g0[i];
        h1[i] = q[i] - g1[i];
    }
    hv[0] = h0[0];
    hv[1] = h0[1];
    hv[2] = h0[2];
    hv[3] = 1.0f;
    vu0Chain(X, mat0, hv);
    hv[0] = h1[0];
    hv[1] = h1[1];
    hv[2] = h1[2];
    hv[3] = 1.0f;
    vu0Chain(Y, mat1, hv);
    for (i = 0; i < 4; i++) {
        K[i] = Y[i] + (X[i] - Y[i]) * q[3];
    }
    vu0Chain(P, gc, K);

    /* perspective divide, fixed point (x16) xyzw, range test on the written lanes */
    qd = 1.0f / P[3];
    for (i = 0; i < 3; i++) {
        Pn[i] = P[i] * qd;
    }
    Pn[3] = P[3];
    for (i = 0; i < 4; i++) {
        I[i] = (s32)(Pn[i] * 16.0f);
    }

    flagv[0] = Pn[0];
    flagv[1] = Pn[1];
    flagv[2] = Pn[3] - 1.0f;
    flagv[3] = 4096.0f - Pn[0];
    flagv[4] = 4096.0f - Pn[1];
    status = 0;
    for (i = 0; i < 5; i++) {
        if (flagv[i] == 0.0f) {
            status = status | 0x40;
        }
        if (flagv[i] < 0.0f) {
            status = status | 0x80;
        }
    }
    status = status & 0xC0;
    if (status != 0) {
        /* vmfir.w vf10, vi1 with vi1 = 0x8000 (16-bit, sign-extended) */
        I[3] = -32768;
    }

    vu0Load(w20, ctx + 0x20);
    for (i = 0; i < 3; i++) {
        o50[i] = w20[i] * qd;
        o60[i] = b15[i] * qd;
    }
    o50[3] = h1[3];
    o60[3] = Y[3];

    vu0Store(ctx + 0x50, o50);
    vu0Store(ctx + 0x60, o60);
    __builtin_memcpy(ctx + 0x30, I, 16);

    return status;
}
