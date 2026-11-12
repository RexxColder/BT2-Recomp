#include "common.h"

void func_00312710(u8 *a0, u8 *a1);
s32 func_00277E68(s32 a0);
s32 func_003B5910(s32 a0, s32 a1, s32 a2);
s32 func_003B6608(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 t0, s32 t1, s32 t2, s32 t3,
                  f32 *c0, f32 *c1, f32 *c2, f32 *c3, u64 extra, s32 one, s32 a15);

/* 0x003B62C8: builds four GS-style vertices (X = 16*x + 0x7000, Y = 16*f(y) + 0x7200, W = 0xFFFFFF)
   from four source points, runs a 3B5910 check on each (any nonzero result is returned at once),
   then calls 3B6608 with the four vertices and four float quads ({f, f, 1, 1} each). */
s32 func_003B62C8(u8 *p0, u8 *p1, u8 *p2, u8 *p3, s32 t0, s32 t1, s32 t2, s32 t3,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  s64 a13, s64 a14, s32 a15, u8 *a16) {
    s32 vtx[4][4];
    s32 prm[4][4];
    f32 c0[4];
    f32 c1[4];
    f32 c2[4];
    f32 c3[4];
    u8 *src[4];
    s32 i;
    s32 r;

    (void)a13;
    (void)a14;

    src[0] = p0;
    src[1] = p1;
    src[2] = p2;
    src[3] = p3;

    for (i = 0; i < 4; i++) {
        func_00312710((u8 *)vtx[i], src[i]);
    }
    for (i = 0; i < 4; i++) {
        vtx[i][0] = 16 * vtx[i][0] + 0x7000;
        vtx[i][1] = 16 * func_00277E68(vtx[i][1]) + 0x7200;
        vtx[i][2] = 0xFFFFFF;
    }

    r = func_003B5910(vtx[0][0], vtx[0][1], vtx[0][2]);
    if (r != 0) {
        return r;
    }
    r = func_003B5910(vtx[1][0], vtx[1][1], vtx[1][2]);
    if (r != 0) {
        return r;
    }
    r = func_003B5910(vtx[2][0], vtx[2][1], vtx[2][2]);
    if (r != 0) {
        return r;
    }
    r = func_003B5910(vtx[3][0], vtx[3][1], vtx[3][2]);
    if (r != 0) {
        return r;
    }

    for (i = 0; i < 4; i++) {
        prm[i][0] = vtx[i][0];
        prm[i][1] = vtx[i][1];
        prm[i][2] = vtx[i][2];
        prm[i][3] = 0;
    }

    c0[0] = f12; c0[1] = f13; c0[2] = 1.0f; c0[3] = 1.0f;
    c1[0] = f14; c1[1] = f15; c1[2] = 1.0f; c1[3] = 1.0f;
    c2[0] = f16; c2[1] = f17; c2[2] = 1.0f; c2[3] = 1.0f;
    c3[0] = f18; c3[1] = f19; c3[2] = 1.0f; c3[3] = 1.0f;

    return func_003B6608((u8 *)prm[0], (u8 *)prm[1], (u8 *)prm[2], (u8 *)prm[3],
                         t0, t1, t2, t3, c0, c1, c2, c3,
                         *(u64 *)(a16 + 0x30), 1, a15);
}
