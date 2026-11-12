#include "common.h"

extern f32 D_00383EFC;
extern f32 D_00383F00;
extern f32 D_00383F04;
extern f32 D_00383F08;
extern f32 D_00383F0C;

extern f32 cosf(f32 x);
extern f32 sinf(f32 x);
extern void func_003126C8(void *dst, void *src);
extern void sceVu0Normalize(void *dst, void *src);
extern void func_00114598(void *mtx, void *a, void *b);
extern void sceVu0ApplyMatrix(void *dst, void *mtx, void *vec);

/* GIF vertex word: x in the low half, y shifted 16 up (both 12.4 fixed point) */
#define PACK_XY(x, y) ((u64)(s64)(s32)((x) << 4) | ((u64)(s64)(s32)((y) << 4) << 16))

#define GIF_RING_HEAD(w2, w4) \
    out[0] = 0x1000000000000002ULL; \
    out[1] = 14; \
    out += 2; \
    out[0] = (w2); \
    out[1] = 0; \
    out += 2; \
    out[0] = (w4); \
    out[1] = 1; \
    out += 2; \
    out[0] = 0x140000000000801FULL; \
    out[1] = 5; \
    out += 2

/* one flat ring (no matrix): 15 pairs of circle points then a closing vertex at angle 0 */
#define FLAT_RING(radius, k) \
    for (i = 0; i < 30;) { \
        f32 ang = (12.0f * (f32)i / 180.0f) * (k); \
        vecA[0] = cosf(ang) * (radius); \
        vecA[1] = sinf(ang) * -(radius); \
        vecB[0] = (vecA[0] * 36.0f) * scale; \
        vecB[1] = (vecA[1] * 36.0f) * scale; \
        px = (s32)vecB[0] + cx; \
        py = (s32)vecB[1] + cy; \
        out[0] = PACK_XY(px, py); \
        ang = (12.0f * (f32)(i + 1) / 180.0f) * (k); \
        vecA[0] = cosf(ang) * (radius); \
        vecA[1] = sinf(ang) * -(radius); \
        vecB[0] = (vecA[0] * 36.0f) * scale; \
        vecB[1] = (vecA[1] * 36.0f) * scale; \
        px = (s32)vecB[0] + cx; \
        py = (s32)vecB[1] + cy; \
        out[1] = PACK_XY(px, py); \
        i += 2; \
        out += 2; \
    } \
    vecA[1] = 0.0f; \
    vecA[0] = (radius); \
    vecB[1] = scale * vecA[1]; \
    vecB[0] = ((radius) * 36.0f) * scale; \
    out[1] = 0; \
    px = (s32)vecB[0] + cx; \
    py = (s32)vecB[1] + cy; \
    out[0] = PACK_XY(px, py); \
    out += 2

/* Builds the GIF packets of a spinning ring effect (a cone ring with up to three rings); returns the end of the packet. */
u64 *func_00114CB0(u64 *out, f32 *prm, void *src, f32 scale) {
    f32 vecA[4];
    f32 vecB[4];
    f32 mtx[16];
    f32 dir[4];
    f32 up[4];
    s32 cx;
    s32 cy;
    s32 px;
    s32 py;
    s32 i = 0;

    __builtin_memset(vecA, 0, 16);
    vecA[3] = 1.0f;
    __builtin_memset(vecB, 0, 16);
    vecB[3] = 1.0f;
    func_003126C8(up, src);
    dir[0] = prm[46];
    dir[2] = prm[54];
    dir[3] = 1.0f;
    up[1] = 0.0f;
    dir[1] = 0.0f;
    sceVu0Normalize(dir, dir);
    func_00114598(mtx, dir, up);

    /* ring 1: rotated by the matrix */
    GIF_RING_HEAD(194, 0x3F80000080FFFFFFULL);
    cx = 0x800;
    cy = 0x800;
    for (i = 0; i < 30;) {
        f32 ang = (12.0f * (f32)i / 180.0f) * D_00383EFC;
        vecA[0] = cosf(ang) * prm[4];
        vecA[2] = sinf(ang) * -prm[4];
        sceVu0ApplyMatrix(vecB, mtx, vecA);
        vecB[1] = (vecB[1] * 36.0f) * scale;
        vecB[0] = (vecB[0] * 36.0f) * scale;
        px = (s32)vecB[0] + cx;
        py = (s32)vecB[1] + cy;
        out[0] = PACK_XY(px, py);
        ang = (12.0f * (f32)(i + 1) / 180.0f) * D_00383EFC;
        vecA[0] = cosf(ang) * prm[4];
        vecA[2] = sinf(ang) * -prm[4];
        sceVu0ApplyMatrix(vecB, mtx, vecA);
        vecB[1] = (vecB[1] * 36.0f) * scale;
        vecB[0] = (vecB[0] * 36.0f) * scale;
        px = (s32)vecB[0] + cx;
        py = (s32)vecB[1] + cy;
        out[1] = PACK_XY(px, py);
        i += 2;
        out += 2;
    }
    vecA[0] = prm[4];
    vecA[2] = 0.0f;
    sceVu0ApplyMatrix(vecB, mtx, vecA);
    vecB[1] = (vecB[1] * 36.0f) * scale;
    vecB[0] = (vecB[0] * 36.0f) * scale;
    out[1] = 0;
    px = (s32)vecB[0] + cx;
    py = (s32)vecB[1] + cy;
    out[0] = PACK_XY(px, py);
    out += 2;

    /* ring 2 */
    if (D_00383F00 < prm[5]) {
        GIF_RING_HEAD(194, 0x3F800000500EBB2DULL);
        i = 0;
        FLAT_RING(prm[1], D_00383F04);
    }
    /* rings 3 and 4 */
    if (prm[5] < 1.0f) {
        GIF_RING_HEAD(69, 0x3F8000005000FFFFULL);
        i = 0;
        FLAT_RING(prm[3], D_00383F08);
        GIF_RING_HEAD(194, 0x3F8000008000FFFFULL);
        i = 0;
        FLAT_RING(prm[3], D_00383F0C);
    }
    return out;
}
