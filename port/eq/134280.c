#include "common.h"
#include "vu0_state.h"

extern void func_00312518(void *arg0, void *arg1);
extern void sceVu0ApplyMatrix(void *arg0, void *arg1, void *arg2);
extern void func_00312680(void *arg0, void *arg1, f32 farg0);
extern void func_00312638(void *arg0, void *arg1, void *arg2);
extern void EftBurst_SetTexture(s32 arg0, s32 arg1, s32 arg2);
extern void *Dma_BeginDirect(void);
extern void Dma_EndDirect(void *arg0);
extern u8 *gBtlCamView;
extern u8 D_0036DC50[0x20];
extern u8 D_0036DC70[0x20];

/* Projects two corners of a quad (D_0036DC50) through the camera matrix and the VU0 screen matrix
   (vf24..vf27) and, when any corner is in front (z > 0), emits a 2-corner sprite GIF packet. */
void func_00134280(u8 *obj) {
    u8 sp[0xC0] __attribute__((aligned(16))); /* asm frame: locals 0x00..0xBF (mtx at 0x70 is 64 bytes; 0xB0/0xB4 used); was 0x80 -> stack smash */
    u8 *corners = sp + 0x10;
    u32 *uv = (u32 *)(sp + 0x30);
    s32 *out = (s32 *)(sp + 0x50);
    u8 *mtx = sp + 0x70;
    f32 *tmp = (f32 *)sp;
    f32 acc[4];
    f32 q;
    s32 num;
    s32 den;
    s32 flags;
    s32 visible = 0;
    f32 scale;
    s32 i;
    s32 k;
    u64 *p;
    s64 alpha;

    __builtin_memcpy(corners, D_0036DC50, 0x20);
    __builtin_memcpy(sp + 0x30, D_0036DC70, 0x20);
    num = *(s32 *)(obj + 0x40);
    *(s32 *)(sp + 0xB0) = num;
    scale = *(f32 *)(obj + 0x4C);
    *(s32 *)(sp + 0xB4) = *(s32 *)(obj + 0x60);
    den = *(s32 *)(obj + 0x44);
    flags = *(s32 *)(obj + 0x50);
    func_00312518(mtx, gBtlCamView);

    for (k = 0; k < 2; k++) {
        sceVu0ApplyMatrix(tmp, mtx, corners + k * 16);
        func_00312680(tmp, tmp, scale);
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
        out[k * 4 + 0] = (s32)(gVu0.vf[5][0] * 16.0f);
        out[k * 4 + 1] = (s32)(gVu0.vf[5][1] * 16.0f);
        out[k * 4 + 2] = (s32)gVu0.vf[5][2];
        out[k * 4 + 3] = (s32)gVu0.vf[5][3];
        if (out[k * 4 + 2] > 0) {
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
    if ((flags & 8) != 0) {
        p[4] = 0x44;
    } else if ((flags & 0x100) == 0) {
        p[4] = 0x48;
    } else {
        p[4] = 0x42;
    }
    p[5] = 0x42;
    p[6] = *(u64 *)(*(u8 **)(obj + 0x48) + 0x30) | 0x5400400002D00ULL;
    p[7] = 6;
    p[8] = 0x33003;
    p[9] = 0x47;
    p[10] = 0x6400000000008001ULL;
    p[11] = 0x52525210;
    p[12] = 0x56;
    if ((flags & 0x40) != 0) {
        p[13] = (u64)*(u32 *)(obj + 0x5C) | ((u64)(s64)*(s32 *)(sp + 0xB4) << 24) | 0x3F80000000000000ULL;
    } else {
        alpha = (num * 80) / den;
        p[13] = ((u64)alpha << 24) | 0x3F80000000505050ULL;
    }
    p[14] = (u64)uv[0] | ((u64)uv[1] << 32);
    p[15] = (u64)(s64)out[0] | ((u64)(s64)out[1] << 16) | ((u64)(s64)out[2] << 32);
    p[16] = (u64)uv[4] | ((u64)uv[5] << 32);
    p[17] = (u64)(s64)out[4] | ((u64)(s64)out[5] << 16) | ((u64)(s64)out[6] << 32);
    Dma_EndDirect(p + 18);
}
