#include "common.h"
#include "vu0_state.h"

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

/* vf1..vf4 = identity rows (VU0 regs written by the vsub/vadd.w/vmr32 chain) and the same rows on the stack
   frame: m[0..3] = x row, m[4..7] = y row, m[8..11] = z row, m[12..15] = w row. */
static void IdentityRows(f32 *m) {
    s32 i;
    static const f32 w[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    for (i = 0; i < 4; i++) {
        gVu0.vf[1][i] = w[i];
        gVu0.vf[2][i] = w[(i + 1) & 3];
        gVu0.vf[3][i] = w[(i + 2) & 3];
        gVu0.vf[4][i] = w[(i + 3) & 3];
    }
    for (i = 0; i < 4; i++) {
        m[12 + i] = gVu0.vf[1][i];
        m[8 + i] = gVu0.vf[2][i];
        m[4 + i] = gVu0.vf[3][i];
        m[i] = gVu0.vf[4][i];
    }
}

/* dst = vf28*row.x + vf29*row.y + vf30*row.z + vf31*row.w (vmulax/vmadday/vmaddaz/vmaddw). */
static void MulRow(s32 dst, f32 *row) {
    f32 acc[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        gVu0.vf[1][i] = row[i];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = gVu0.vf[28][i] * row[0];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[29][i] * row[1];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[30][i] * row[2];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = acc[i];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[dst][i] = acc[i] + gVu0.vf[31][i] * row[3];
    }
}

/* Applies one axis rotation (axis 0 = X, 1 = Y, 2 = Z) to the matrix rows vf28..vf30. */
static void RotStep(f32 *m, s32 axis, f32 ang) {
    f32 c = cosf(ang);
    f32 s;

    IdentityRows(m);
    if (axis == 1) {
        m[0] = c;
        s = sinf(ang);
        m[8] = s;
        m[10] = m[0];
        m[2] = -s;
        MulRow(3, m + 0);
        MulRow(4, m + 8);
        __builtin_memcpy(gVu0.vf[28], gVu0.vf[3], 16);
        __builtin_memcpy(gVu0.vf[30], gVu0.vf[4], 16);
    } else if (axis == 0) {
        m[5] = c;
        s = sinf(ang);
        m[9] = s;
        m[10] = m[5];
        m[6] = -s;
        MulRow(3, m + 4);
        MulRow(4, m + 8);
        __builtin_memcpy(gVu0.vf[29], gVu0.vf[3], 16);
        __builtin_memcpy(gVu0.vf[30], gVu0.vf[4], 16);
    } else {
        m[0] = c;
        s = sinf(ang);
        m[4] = s;
        m[5] = m[0];
        m[1] = -s;
        MulRow(4, m + 0);
        MulRow(3, m + 4);
        __builtin_memcpy(gVu0.vf[28], gVu0.vf[4], 16);
        __builtin_memcpy(gVu0.vf[29], gVu0.vf[3], 16);
    }
}

/* Transforms the vector at vec by the matrix in vf28..vf31 (result in vf31), then composes three axis
   rotations from the euler angles ang[0..2] (X, Y, Z) into vf28..vf30 in the order selected by `order`. */
void func_0029C980(f32 *vec, f32 *ang, u32 order) {
    f32 m[16];
    f32 acc[4];
    s32 i;
    /* axis sequence per order: 0 = X (ang[0]), 1 = Y (ang[1]), 2 = Z (ang[2]) */
    static const u8 seq[6][3] = {{1, 0, 2}, {1, 2, 0}, {2, 1, 0}, {2, 0, 1}, {0, 1, 2}, {0, 2, 1}};

    for (i = 0; i < 4; i++) {
        gVu0.vf[1][i] = vec[i];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = gVu0.vf[28][i] * gVu0.vf[1][0];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[29][i] * gVu0.vf[1][1];
    }
    for (i = 0; i < 4; i++) {
        acc[i] = acc[i] + gVu0.vf[30][i] * gVu0.vf[1][2];
    }
    for (i = 0; i < 4; i++) {
        gVu0.acc[i] = acc[i];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[2][i] = acc[i] + gVu0.vf[31][i] * gVu0.vf[1][3];
    }
    for (i = 0; i < 4; i++) {
        gVu0.vf[31][i] = gVu0.vf[2][i];
    }
    if (order >= 6) {
        return;
    }
    for (i = 0; i < 3; i++) {
        RotStep(m, seq[order][i], ang[seq[order][i]]);
    }
}
