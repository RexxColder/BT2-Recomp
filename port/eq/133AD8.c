#include "common.h"
#include "vu0_state.h"

extern void func_00312680(void *arg0, void *arg1, f32 farg0);
extern void func_00312638(void *arg0, void *arg1, void *arg2);
extern void EftBurst_SetTexture(s32 arg0, s32 arg1, s32 arg2);
extern void *Dma_BeginDirect(void);
extern void Dma_EndDirect(void *arg0);
extern u8 D_0036DBD0[64];

/* Projects the four corners of a unit quad (scaled by obj+0x4C and moved by obj+0) through the
   VU0 screen matrix (vf24..vf27, perspective divide, xy in 12.4 fixed) and, when any corner is in
   front (z > 0), emits a textured sprite GIF packet whose alpha scales with obj+0x40 / obj+0x44. */
void func_00133AD8(u8 *obj) {
    f32 tmp[4];
    u8 corners[64];
    f32 uv[4][4];
    s32 out[4][4];
    f32 acc[4];
    f32 q;
    f32 scale = *(f32 *)(obj + 0x4C);
    s32 num = *(s32 *)(obj + 0x40);
    s32 den = *(s32 *)(obj + 0x44);
    s32 visible = 0;
    s32 i;
    s32 k;
    u64 *p;
    s32 alpha;

    __builtin_memcpy(corners, D_0036DBD0, 64);
    __builtin_memset(uv, 0, 64);
    uv[1][0] = 1.0f;
    uv[2][1] = 1.0f;
    uv[3][0] = 1.0f;
    uv[3][1] = 1.0f;

    for (k = 0; k < 4; k++) {
        func_00312680(tmp, corners + k * 16, scale);
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
    p[5] = 0x42;
    p[4] = 0x48;
    p[7] = 6;
    p[6] = *(u64 *)(*(u8 **)(obj + 0x48) + 0x30) | 0x5400400002D00ULL;
    p[8] = 0x73003;
    p[9] = 0x47;
    p[10] = 0x2400000000008001ULL;
    p[11] = 0x10;
    p[12] = 0x54;
    if (den < num * 2) {
        alpha = ((den - num) * 16) / den;
    } else {
        alpha = (num * 16) / den;
    }
    p[13] = ((u64)(s64)alpha << 24) | 0x3F80000000808080ULL;
    p[14] = 0x8400000000008001ULL;
    p[15] = 0x52525252;
    p += 16;
    for (k = 0; k < 4; k++) {
        p[0] = (u64)*(u32 *)&uv[k][0] | ((u64)*(u32 *)&uv[k][1] << 32);
        p[1] = (u64)(s64)out[k][0] | ((u64)(s64)out[k][1] << 16) | ((u64)(s64)out[k][2] << 32);
        p += 2;
    }
    Dma_EndDirect(p);
}
