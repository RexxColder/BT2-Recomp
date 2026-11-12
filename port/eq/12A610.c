#include "common.h"

void sceVu0InversMatrix(void *arg0, s32 arg1);
void sceVu0Normalize(void *arg0, void *arg1);
f32 sceVu0InnerProduct(void *arg0, void *arg1);
void sceVu0ApplyMatrix(void *arg0, void *arg1, void *arg2);

/* 0x0012A610: shade a normal-map row. For each texel of src (3 bytes: x, y, z, then one pad byte) the normal is
   rebuilt as 2 * (n . nrm) * n - nrm with the 4x4 matrix M = inverse of m applied (sceVu0ApplyMatrix); its
   dot with the light block vecs (3 rows, via v36 = -translation of M) scales the RGB bytes of dst by
   scale * 255 (clamped 0..255). Byte +3 of each dst texel gets +0x80. The asm leaves the last clamp in v0;
   ctx.h says void, so this is void. */
void func_0012A610(u8 *dst, u8 *src, u8 *m, u8 *vecs, u8 *nrm, f32 scale) {
    f32 M[16];
    f32 v36[4];
    f32 v35[4];
    f32 v30[4];
    f32 v31[4];
    f32 v29[4];
    s32 i;
    s32 x;
    s32 y;
    s32 z;
    s32 c;
    f32 dotv;
    f32 k;

    __builtin_memset(v36, 0, sizeof(v36));
    v36[3] = 1.0f;
    sceVu0InversMatrix((void *)M, (s32)m);
    v36[0] = -M[8];
    v36[1] = -M[9];
    v36[2] = -M[10];
    M[12] = 0.0f;
    M[14] = 0.0f;
    M[13] = 0.0f;

    v35[0] = sceVu0InnerProduct((void *)v36, (void *)vecs);
    v35[1] = sceVu0InnerProduct((void *)v36, (void *)(vecs + 0x10));
    v35[3] = 1.0f;
    v35[2] = sceVu0InnerProduct((void *)v36, (void *)(vecs + 0x20));

    i = 0;
    do {
        x = src[0];
        y = src[1];
        z = src[2];
        src += 4;
        v31[3] = 1.0f;
        i = i + 1;
        v31[0] = (f32)x - 128.0f;
        v31[1] = (f32)y - 128.0f;
        v31[2] = (f32)z - 128.0f;
        sceVu0Normalize((void *)v31, (void *)v31);
        dotv = sceVu0InnerProduct((void *)nrm, (void *)v31);
        k = dotv + dotv;
        v30[3] = 1.0f;
        v30[2] = (v31[2] * k) - *(f32 *)(nrm + 8);
        v30[0] = (v31[0] * k) - *(f32 *)(nrm + 0);
        v30[1] = (v31[1] * k) - *(f32 *)(nrm + 4);
        sceVu0ApplyMatrix((void *)v29, (void *)M, (void *)v30);
        dotv = sceVu0InnerProduct((void *)v35, (void *)v29);

        {
            s32 r = (s32)(dotv * (scale * 255.0f));
            if (r < 0) {
                r = 0;
            }
            if (r >= 256) {
                r = 255;
            }
            c = r;
        }
        dst[3] += 0x80;
        dst[0] = (u8)(dst[0] + c);
        dst[1] = (u8)(dst[1] + c);
        dst[2] = (u8)(dst[2] + c);
        dst += 4;
    } while (i < 256);
}
