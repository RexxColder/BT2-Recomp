#include "common.h"

void func_0027F030(void *arg0, void *arg1);

/* 0x002806E0: build a 256-entry colour table (4 bytes each) at dst from the unit block src.
   The table of floats comes from func_0027F030(src + 0x4D0). Entry idx = i with bits 3 and 4 swapped
   (i & 0xE7 | (i & 8) << 1 | (i & 0x10) >> 1). Flag +0x5A2 picks the scaled-by-128 path (A) or the
   scaled-by-255 path (B); flag +0x5A1 zeroes entry 255. Alpha: 0x80 in A, a clamped value in B. */
void func_002806E0(u8 *dst, u8 *src) {
    f32 tbl[256];
    f32 k0;
    f32 k1;
    f32 k2;
    f32 kc;
    s32 i;

    __builtin_memset(tbl, 0, sizeof(tbl));
    func_0027F030((void *)(src + 0x4D0), (void *)tbl);

    k0 = *(f32 *)(src + 0x4C0);
    k1 = *(f32 *)(src + 0x4C4);
    k2 = *(f32 *)(src + 0x4C8);
    kc = *(f32 *)(src + 0x4CC);

    if (src[0x5A2] != 0) {
        for (i = 0; i < 256; i++) {
            u32 idx = ((u32)i & 0xE7) | (((u32)i & 8) << 1) | (((u32)i & 0x10) >> 1);
            u8 *e = dst + idx * 4;
            f32 t = tbl[i];

            if (src[0x5A1] != 0 && i == 255) {
                e[3] = 0;
                e[0] = 0;
                e[1] = 0;
                e[2] = 0;
            } else {
                e[0] = (u8)(s32)(((t * k0) * 128.0f) * kc);
                e[1] = (u8)(s32)(((t * k1) * 128.0f) * kc);
                e[2] = (u8)(s32)(((t * k2) * 128.0f) * kc);
                e[3] = 0x80;
            }
        }
    } else {
        for (i = 0; i < 256; i++) {
            u32 idx = ((u32)i & 0xE7) | (((u32)i & 8) << 1) | (((u32)i & 0x10) >> 1);
            u8 *e = dst + idx * 4;
            f32 t = tbl[i];

            if (src[0x5A1] != 0 && i == 255) {
                e[3] = 0;
                e[0] = 0;
                e[1] = 0;
                e[2] = 0;
            } else {
                f32 v = (t * 128.0f) * kc;

                e[0] = (u8)(s32)(k0 * 255.0f);
                e[1] = (u8)(s32)(k1 * 255.0f);
                e[2] = (u8)(s32)(k2 * 255.0f);
                if (v >= 2147483648.0f) {
                    e[3] = (u8)(((u32)(s32)(v - 2147483648.0f)) | 0x80000000u);
                } else {
                    e[3] = (u8)(s32)v;
                }
            }
        }
    }
}
