#include "common.h"

extern void func_0012D868(s32 *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 *arg4, f32 *arg5);
extern s32 func_001B75F8(s32 *arg0, s32 arg1);
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* Projects a 4-vertex quad (matrix a1, vectors a0) and queues a 0x90-byte GIF packet (four
   coloured vertices with st and 24-bit z) into the depth-sorted list D_00387AE0, bucket by
   (sum of z) >> 10 within the layer given by layer. Skips when a vertex fails func_001B75F8. */
void func_001B6320(f32 *verts, f32 *mtx, u8 r, u8 g, u8 b, u8 a, u64 *tag, s32 layer) {
    f32 st[16];
    f32 tex[16];
    s32 scr[4][4];
    u8 *rec;
    u8 *bucket;
    u8 *prev;
    s32 k;
    s32 depth;

    for (k = 0; k < 16; k++) {
        tex[k] = 0.0f;
    }
    tex[2] = 1.0f;
    tex[4] = 1.0f;
    tex[6] = 1.0f;
    tex[9] = 1.0f;
    tex[10] = 1.0f;
    tex[12] = 1.0f;
    tex[13] = 1.0f;
    tex[14] = 1.0f;
    func_0012D868(&scr[0][0], mtx, verts, 4, st, tex);
    for (k = 0; k < 4; k++) {
        if (!func_001B75F8(scr[k], 4)) {
            return;
        }
    }
    rec = D_00387AD8;
    D_00387AD8 = rec + 0x90;
    if (rec == 0) {
        return;
    }
    *(u64 *)(rec + 0x20) = 0x5C;
    *(u64 *)(rec + 0x00) = 0xA0000008ULL;
    *(u64 *)(rec + 0x10) = 0xE400000000008001ULL;
    *(u64 *)(rec + 0x18) = 0x42142142142160ULL;
    for (k = 0; k < 4; k++) {
        u8 *v = rec + 0x30 + k * 0x18;
        u64 w;

        v[0] = r;
        v[1] = g;
        v[2] = b;
        v[3] = a;
        *(f32 *)(v + 4) = st[k * 4 + 2];
        *(f32 *)(v + 8) = st[k * 4 + 0];
        *(f32 *)(v + 0xC) = st[k * 4 + 1];
        *(u16 *)(v + 0x10) = (u16)scr[k][0];
        *(u16 *)(v + 0x12) = (u16)scr[k][1];
        w = *(u64 *)(v + 0x10);
        w = (w & 0xFF000000FFFFFFFFULL) | ((u64)(s64)(scr[k][2] & 0xFFFFFF) << 32);
        *(u64 *)(v + 0x10) = w;
        v[0x17] = 0xFF;
    }
    *(u64 *)(rec + 0x28) = *tag;
    depth = (scr[0][2] + scr[3][2] + scr[2][2] + scr[1][2]) >> 10;
    if (depth < 0) {
        bucket = D_00387AE0 + layer * 8;
    } else if (depth < 0x1000) {
        bucket = D_00387AE0 + (depth * 2 + layer) * 8;
    } else {
        bucket = D_00387AE0 + layer * 8 + 0xFFF0;
    }
    prev = *(u8 **)(bucket + 4);
    *(u8 **)(prev + 4) = rec;
    *(u8 **)(bucket + 4) = rec;
}
