#include "common.h"

f32 sqrtf(f32 arg0);
f32 fabsf(f32 arg0);
void *memset(void *dst, s32 val, u32 n);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 sceVu0InnerProduct(void *arg0, void *arg1);
void sceVu0Normalize(void *arg0, void *arg1);
void func_00312FB0(void *arg0, void *arg1, f32 farg0);
void func_003126C8(void *arg0, void *arg1);
f32 func_0027EDD0(void *arg0, void *arg1, void *arg2, void *arg3, s32 arg4);

/* 0x0027F030: builds three 0x40-byte frames from the object at arg0 and writes the 0..255 table at arg0+0xC0. */
void func_0027F030(void *arg0, void *arg1) {
    u8 fr[0x10];
    u8 *s2;
    u8 *s5;
    u8 *s0;
    u8 *s1;
    u8 *s4;
    u8 *o;
    s32 s3;
    s32 cntf;
    s32 n;
    f32 fa;
    f32 fb;
    f32 f1;
    f32 dot;
    f32 len1;
    f32 len2;

    s2 = (u8 *)arg0;
    s5 = (u8 *)arg1;

    s0 = s2;
    for (s3 = 0; s3 < 3; s3++) {
        memset(fr, 0, 16);
        *(f32 *)(fr + 0xC) = 1.0f;
        if (s3 != 0 && s3 != 2) {
            s4 = s0 + 0x40;
            s1 = s0 - 0x40;

            func_00312650(fr, s4, s0);
            dot = sceVu0InnerProduct(fr, fr);
            len1 = sqrtf(fabsf(dot));
            func_00312650(fr, s4, s1);
            sceVu0Normalize(fr, fr);
            func_00312FB0(fr, fr, len1);
            func_003126C8(s0 + 0x20, fr);

            func_00312650(fr, s1, s0);
            dot = sceVu0InnerProduct(fr, fr);
            len2 = sqrtf(fabsf(dot));
            func_00312650(fr, s1, s4);
            sceVu0Normalize(fr, fr);
            func_00312FB0(fr, fr, len2);
            func_003126C8(s0 + 0x10, fr);
        }
        s0 += 0x40;
    }

    cntf = (s32)*(f32 *)s2;
    *(s32 *)(s2 + 0xC0) = 0;
    if (cntf > 0) {
        o = s5;
        s3 = 0;
        do {
            *(s32 *)o = 0;
            o += 4;
            s3 += 1;
            *(s32 *)(s2 + 0xC0) += 1;
        } while (s3 < cntf);
    }

    f1 = 0.0f;
    for (s3 = 0; s3 < 2; s3++) {
        if (s3 == 0) {
            fa = *(f32 *)(s2 + 0x40);
            fb = *(f32 *)(s2 + 0);
        } else {
            fa = *(f32 *)(s2 + 0x80);
            fb = *(f32 *)(s2 + 0x40);
        }
        n = (s32)fa - (s32)fb;
        f1 = func_0027EDD0(s2, s5, s2 + 0x40 * s3, s2 + 0x40 * s3 + 0x40, n);
    }

    s3 = *(s32 *)(s2 + 0xC0);
    if (s3 < 0x100) {
        fa = f1 / 255.0f;
        o = s5 + 4 * s3;
        do {
            s3 += 1;
            *(f32 *)o = fa;
            o += 4;
        } while (s3 < 0x100);
    }
}
