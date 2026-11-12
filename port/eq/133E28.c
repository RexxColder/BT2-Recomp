#include "common.h"
#include "vu0_state.h"

extern void func_003126C8(void *arg0, void *arg1);
extern void func_00312638(void *arg0, void *arg1, void *arg2);
extern void sceVu0UnitMatrix(void *m);
extern void sceVu0RotMatrixY(void *d, void *s, f32 angle);
extern void sceVu0RotMatrixZ(void *d, void *s, f32 angle);
extern void sceVu0MulMatrix(void *d, void *a, void *b);
extern void sceVu0ApplyMatrix(void *d, void *m, void *v);
extern void EftBurst_SetTexture(s32 arg0, s32 arg1, s32 arg2);
extern void *Dma_BeginDirect(void);
extern void Dma_EndDirect(void *arg0);
extern u8 D_0036DC10[64];

/* Variant of 133AD8: corners optionally scaled in x/y (flags 0x10/0x20) and rotated (flag 0x80,
   angles at +0x20/+0x24/+0x28); projects through the VU0 screen matrix and emits a sprite packet. */
void func_00133E28(u8 *obj) {
    f32 tmp[4];
    u8 corners[64];
    f32 uv[4][4];
    s32 out[4][4];
    f32 m1[16];
    f32 m2[16];
    f32 acc[4];
    f32 q;
    s32 flags = *(s32 *)(obj + 0x50);
    s32 scaleX = flags & 0x10;
    s32 scaleY = flags & 0x20;
    s32 rotate = flags & 0x80;
    f32 scale = *(f32 *)(obj + 0x4C);
    s32 num = *(s32 *)(obj + 0x40);
    s32 den = *(s32 *)(obj + 0x44);
    s32 mul = *(s32 *)(obj + 0x60);
    s32 visible = 0;
    s32 i;
    s32 k;
    u64 *p;
    s32 alpha;

    __builtin_memcpy(corners, D_0036DC10, 64);
    __builtin_memset(uv, 0, 64);
    uv[1][0] = 1.0f;
    uv[2][1] = 1.0f;
    uv[3][0] = 1.0f;
    uv[3][1] = 1.0f;

    for (k = 0; k < 4; k++) {
        func_003126C8(tmp, corners + k * 16);
        if (scaleX) {
            tmp[0] = tmp[0] * scale;
        }
        if (scaleY) {
            tmp[1] = tmp[1] * scale;
        }
        if (rotate) {
            sceVu0UnitMatrix(m1);
            sceVu0RotMatrixY(m1, m1, *(f32 *)(obj + 0x24));
            sceVu0UnitMatrix(m2);
            sceVu0RotMatrixZ(m2, m2, *(f32 *)(obj + 0x28));
            sceVu0MulMatrix(m1, m2, m1);
            sceVu0UnitMatrix(m2);
            sceVu0RotMatrixY(m2, m2, *(f32 *)(obj + 0x20));
            sceVu0MulMatrix(m1, m1, m2);
            sceVu0ApplyMatrix(tmp, m1, tmp);
        }
        func_00312638(tmp, tmp, obj);
        tmp[3] = 1.0f;
        for (i = 0; i < 4; i++) {
            gVu0.vf[4][i] = tmp[i];
        }
        for (i = 0; i < 4; i++) {
            acc[i] = gVu0.vf[24][i] * gVu0.vf[4][0];
        }
        for (i = 0; i < 4; i++) {
            acc[i] = acc[i] + gVu0.vf[25][i] * gVu0.vf[4][1];
        }
        for (i = 0; i < 4; i++) {
            acc[i] = acc[i] + gVu0.vf[26][i] * gVu0.vf[4][2];
        }
        for (i = 0; i < 4; i++) {
            gVu0.vf[5][i] = acc[i] + gVu0.vf[27][i] * gVu0.vf[4][3];
        }
        q = 1.0f / gVu0.vf[5][3];
        for (i = 0; i < 3; i++) {
            gVu0.vf[5][i] = gVu0.vf[5][i] * q;
            gVu0.vf[6][i] = gVu0.vf[6][i] * q;
        }
        out[k][0] = (s32)(gVu0.vf[5][0] * 16.0f);
        out[k][1] = (s32)(gVu0.vf[5][1] * 16.0f);
        out[k][2] = (s32)gVu0.vf[5][2];
        out[k][3] = (s32)gVu0.vf[5][3];
        if (out[k][2] > 0) {
            visible++;
        }
    }
    if (visible == 0) {
        return;
    }

    EftBurst_SetTexture(*(s32 *)(obj + 0x48), 0x2D00, 0x2A00);
    p = (u64 *)Dma_BeginDirect();
    p[0] = 0x1000000000008004ULL;
    p[1] = 0xE;
    p[2] = 0x1310000E0ULL;
    p[3] = 0x4E;
    p[4] = (*(s32 *)(obj + 0x50) & 8) ? 0x44 : 0x48;
    p[5] = 0x42;
    p[6] = *(u64 *)(*(u8 **)(obj + 0x48) + 0x30) | 0x5400400002D00ULL;
    p[7] = 6;
    p[8] = 0x73003;
    p[9] = 0x47;
    p[10] = 0x2400000000008001ULL;
    p[11] = 0x10;
    p[12] = 0x54;
    alpha = (mul * num) / den;
    if (flags & 0x40) {
        p[13] = (u64)*(u32 *)(obj + 0x5C) | ((u64)(s64)alpha << 24) | 0x3F80000000000000ULL;
    } else {
        p[13] = ((u64)(s64)alpha << 24) | 0x3F80000000805050ULL;
    }
    p[14] = 0x2400000000008004ULL;
    p[15] = 0x52;
    p += 16;
    for (k = 0; k < 4; k++) {
        p[0] = (u64)*(u32 *)&uv[k][0] | ((u64)*(u32 *)&uv[k][1] << 32);
        p[1] = (u64)(s64)out[k][0] | ((u64)(s64)out[k][1] << 16) | ((u64)(s64)out[k][2] << 32);
        p += 2;
    }
    Dma_EndDirect(p);
}
